document.getElementById('numProcesses').addEventListener('input', createProcessInputs);
document.getElementById('run').addEventListener('click', runScheduler);
document.getElementById('reset').addEventListener('click', resetForm);

createProcessInputs();

function createProcessInputs() {
    const numProcesses = document.getElementById('numProcesses').value;
    const processInputs = document.getElementById('processInputs');
    processInputs.innerHTML = '';

    for (let i = 0; i < numProcesses; i++) {
        const div = document.createElement('div');
        div.className = 'form-group';

        const label = document.createElement('label');
        label.textContent = `Process ${i + 1}:`;
        div.appendChild(label);

        const arrivalInput = document.createElement('input');
        arrivalInput.type = 'number';
        arrivalInput.placeholder = 'Arrival Time';
        arrivalInput.required = true;
        arrivalInput.className = 'arrivalTime';
        div.appendChild(arrivalInput);

        const burstInput = document.createElement('input');
        burstInput.type = 'number';
        burstInput.placeholder = 'Burst Time';
        burstInput.required = true;
        burstInput.className = 'burstTime';
        div.appendChild(burstInput);

        const priorityInput = document.createElement('input');
        priorityInput.type = 'number';
        priorityInput.placeholder = 'Priority';
        priorityInput.required = true;
        priorityInput.className = 'priority';
        div.appendChild(priorityInput);

        processInputs.appendChild(div);
    }
}

async function runScheduler() {
    const contextSwitchTime = document.getElementById('contextSwitchTime').value;
    const numProcesses = document.getElementById('numProcesses').value;
    const processInputs = document.querySelectorAll('#processInputs .form-group');

    const processes = [];
    processInputs.forEach((inputGroup, index) => {
        const name = `P${index + 1}`;
        const arrivalTime = inputGroup.querySelector('.arrivalTime').value;
        const burstTime = inputGroup.querySelector('.burstTime').value;
        const priority = inputGroup.querySelector('.priority').value;
        processes.push({ name, arrivalTime, burstTime, priority });
    });

    try {
        const response = await fetch('http://127.0.0.1:5000/run_scheduler', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ contextSwitchTime, processes })
        });

        if (response.ok) {
            const data = await response.json();
            console.log('Scheduler output:', data);  // Debugging: log response data
            displayOutput(data);
            generateCharts(data);
        } else {
            const errorData = await response.json();
            console.error('Failed to fetch data from server:', errorData.error);
            document.getElementById('output').textContent = `Error: ${errorData.error}`;
        }
    } catch (error) {
        console.error('Error occurred:', error);
        document.getElementById('output').textContent = `Error: ${error.message}`;
    }
}

function displayOutput(data) {
    const outputElement = document.getElementById('output');
    outputElement.innerHTML = ''; // Clear previous output

    for (const [algorithm, result] of Object.entries(data)) {
        if (!result || !result.rows || !result.headers) {
            console.error(`Missing data for algorithm ${algorithm}`, result);
            continue;
        }

        const headers = result.headers;
        const rows = result.rows;

        let tableHTML = `<h2>${algorithm}</h2>`;
        tableHTML += '<table><thead><tr>';
        headers.forEach(header => {
            tableHTML += `<th>${header ? header.trim() : ''}</th>`;
        });
        tableHTML += '</tr></thead><tbody>';

        rows.forEach(row => {
            tableHTML += '<tr>';
            row.forEach(column => {
                tableHTML += `<td>${column ? column.trim() : ''}</td>`;
            });
            tableHTML += '</tr>';
        });

        tableHTML += '</tbody></table>';
        outputElement.insertAdjacentHTML('beforeend', tableHTML);

        // Add canvases for charts
        outputElement.insertAdjacentHTML('beforeend', `<canvas id="${algorithm}WaitingTimeChart" width="400" height="400"></canvas>`);
        outputElement.insertAdjacentHTML('beforeend', `<canvas id="${algorithm}TurnaroundTimeChart" width="400" height="400"></canvas>`);
    }
}

function generateCharts(data) {
    for (const [algorithm, result] of Object.entries(data)) {
        if (!result.rows) continue;

        const processNames = [];
        const waitingTimes = [];
        const turnaroundTimes = [];

        result.rows.forEach(row => {
            processNames.push(row[0] ? row[0].trim() : '');
            turnaroundTimes.push(parseFloat(row[4] ? row[4].trim() : 0)); // Correct index for turnaround time
            waitingTimes.push(parseFloat(row[5] ? row[5].trim() : 0)); // Correct index for waiting time
        });

        const waitingTimeCtx = document.getElementById(`${algorithm}WaitingTimeChart`).getContext('2d');
        const turnaroundTimeCtx = document.getElementById(`${algorithm}TurnaroundTimeChart`).getContext('2d');

        new Chart(waitingTimeCtx, {
            type: 'pie',
            data: {
                labels: processNames,
                datasets: [{
                    label: 'Waiting Time',
                    data: waitingTimes,
                    backgroundColor: generateColors(waitingTimes.length),
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: {
                        position: 'top',
                    },
                    title: {
                        display: true,
                        text: `Waiting Time of Processes (${algorithm})`
                    }
                }
            }
        });

        new Chart(turnaroundTimeCtx, {
            type: 'pie',
            data: {
                labels: processNames,
                datasets: [{
                    label: 'Turnaround Time',
                    data: turnaroundTimes,
                    backgroundColor: generateColors(turnaroundTimes.length),
                }]
            },
            options: {
                responsive: true,
                plugins: {
                    legend: {
                        position: 'top',
                    },
                    title: {
                        display: true,
                        text: `Turnaround Time of Processes (${algorithm})`
                    }
                }
            }
        });
    }
}

function resetForm() {
    document.getElementById('numProcesses').value = '1';
    document.getElementById('contextSwitchTime').value = '0';
    document.getElementById('processInputs').innerHTML = '';
    document.getElementById('output').innerHTML = '';
    createProcessInputs();  // Reset process inputs as well
}

function generateColors(count) {
    const colors = [];
    for (let i = 0; i < count; i++) {
        colors.push(`hsl(${i * (360 / count)}, 70%, 60%)`);
    }
    return colors;
}
