document.getElementById('numProcesses').addEventListener('input', createProcessInputs);
document.getElementById('algorithm').addEventListener('change', createProcessInputs);
document.getElementById('run').addEventListener('click', runScheduler);
document.getElementById('reset').addEventListener('click', resetForm);

// Initialize form with one process input
createProcessInputs();

function createProcessInputs() {
    const numProcesses = document.getElementById('numProcesses').value;
    const processInputs = document.getElementById('processInputs');
    const algorithm = document.getElementById('algorithm').value;
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

        if (algorithm == '5') { // Priority Scheduling
            const priorityInput = document.createElement('input');
            priorityInput.type = 'number';
            priorityInput.placeholder = 'Priority';
            priorityInput.required = true;
            priorityInput.className = 'priority';
            div.appendChild(priorityInput);
        }

        processInputs.appendChild(div);
    }
}

async function runScheduler() {
    const algorithm = document.getElementById('algorithm').value;
    const contextSwitchTime = document.getElementById('contextSwitchTime').value;
    const numProcesses = document.getElementById('numProcesses').value;
    const processInputs = document.querySelectorAll('#processInputs .form-group');

    const processes = [];
    processInputs.forEach((inputGroup, index) => {
        const name = `P${index + 1}`;
        const arrivalTime = inputGroup.querySelector('.arrivalTime').value;
        const burstTime = inputGroup.querySelector('.burstTime').value;
        const priorityInput = inputGroup.querySelector('.priority');
        const priority = priorityInput ? priorityInput.value : 0;
        processes.push({ name, arrivalTime, burstTime, priority });
    });

    try {
        const response = await fetch('http://127.0.0.1:5000/run_scheduler', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ algorithm, contextSwitchTime, processes })
        });

        if (response.ok) {
            const data = await response.json();
            console.log('Scheduler output:', data);  // Debugging: log response data
            displayOutput(data.output);
            createPieCharts(data.output);  // Call function to create pie charts
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

function displayOutput(output) {
    const outputElement = document.getElementById('output');
    const rows = output.trim().split('\n');
    const headers = rows[0].split(' | ');

    let tableHTML = '<table><thead><tr>';
    headers.forEach(header => {
        tableHTML += `<th>${header.trim()}</th>`;
    });
    tableHTML += '</tr></thead><tbody>';

    rows.slice(1).forEach(row => {
        const columns = row.split(' | ');
        tableHTML += '<tr>';
        columns.forEach(column => {
            tableHTML += `<td>${column.trim()}</td>`;
        });
        tableHTML += '</tr>';
    });

    tableHTML += '</tbody></table>';
    outputElement.innerHTML = tableHTML;

    // Append additional metrics
    const avgWaitingTime = rows[rows.length - 3].split(': ')[1];
    const avgTurnaroundTime = rows[rows.length - 2].split(': ')[1];
    const cpuUtilization = rows[rows.length - 1].split(': ')[1];

    const metricsHTML = `
        <p>Average Waiting Time: ${avgWaitingTime}</p>
        <p>Average Turnaround Time: ${avgTurnaroundTime}</p>
        <p>CPU Utilization: ${cpuUtilization}</p>
    `;
    outputElement.insertAdjacentHTML('beforeend', metricsHTML);
}

function resetForm() {
    document.getElementById('algorithm').value = '1';
    document.getElementById('numProcesses').value = '1';
    document.getElementById('contextSwitchTime').value = '0';
    document.getElementById('processInputs').innerHTML = '';
    document.getElementById('output').innerHTML = '';
    createProcessInputs();  // Reset process inputs as well
}

// Variables to hold Chart instances
let waitingTimeChart = null;
let turnaroundTimeChart = null;

function createPieCharts(output) {
    const rows = output.trim().split('\n').slice(1, -3);
    const processNames = [];
    const waitingTimes = [];
    const turnaroundTimes = [];
    const finishTimes = [];

    rows.forEach(row => {
        const columns = row.split(' | ');
        if (columns.length >= 5) { // Adjusted for new table structure
            processNames.push(columns[0].trim());
            finishTimes.push(parseFloat(columns[3].trim())); // Correct index for finish time
            turnaroundTimes.push(parseFloat(columns[4].trim())); // Correct index for turnaround time
            waitingTimes.push(parseFloat(columns[5].trim())); // Correct index for waiting time
        }
    });

    const waitingTimeCtx = document.getElementById('waitingTimeChart').getContext('2d');
    const turnaroundTimeCtx = document.getElementById('turnaroundTimeChart').getContext('2d');

    // Destroy existing charts if they exist
    if (waitingTimeChart) {
        waitingTimeChart.destroy();
    }
    if (turnaroundTimeChart) {
        turnaroundTimeChart.destroy();
    }

    waitingTimeChart = new Chart(waitingTimeCtx, {
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
                    text: 'Waiting Time of Processes'
                }
            }
        }
    });

    turnaroundTimeChart = new Chart(turnaroundTimeCtx, {
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
                    text: 'Turnaround Time of Processes'
                }
            }
        }
    });
}

function generateColors(count) {
    const colors = [];
    for (let i = 0; i < count; i++) {
        colors.push(`hsl(${i * (360 / count)}, 70%, 60%)`);
    }
    return colors;
}
