document.getElementById('numProcesses').addEventListener('input', createProcessInputs);
document.getElementById('run').addEventListener('click', runScheduler);
document.getElementById('reset').addEventListener('click', resetForm);

// Initialize form with one process input
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
        processes.push({ name, arrivalTime, burstTime });
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
}

function resetForm() {
    document.getElementById('algorithm').value = '1';
    document.getElementById('numProcesses').value = '1';
    document.getElementById('contextSwitchTime').value = '0';
    document.getElementById('processInputs').innerHTML = '';
    document.getElementById('output').innerHTML = '';
    createProcessInputs();  // Reset process inputs as well
}
