from flask import Flask, request, jsonify
import subprocess
from flask_cors import CORS
import os

app = Flask(__name__)
CORS(app)

SCHEDULER_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../scheduler')

@app.route('/run_scheduler', methods=['POST'])
def run_scheduler():
    data = request.json
    context_switch_time = data['contextSwitchTime']
    processes = data['processes']

    input_data = f"{len(processes)}\n"
    for process in processes:
        input_data += f"{process['name']} {process['arrivalTime']} {process['burstTime']} {process.get('priority', 0)}\n"

    print("Input Data:", input_data)

    input_file = os.path.join(SCHEDULER_DIR, 'input.txt')
    with open(input_file, 'w') as f:
        f.write(input_data)

    algorithms = {
        'FCFS': '1',
        'SJF': '3',
        'SRTF': '4',
        'Priority': '5'
    }
    
    results = {}
    
    for name, alg in algorithms.items():
        command = f"{os.path.join(SCHEDULER_DIR, 'scheduler')} {alg} {context_switch_time} < {input_file}"
        result = subprocess.run(command, shell=True, capture_output=True, text=True, cwd=SCHEDULER_DIR)
        output = result.stdout.strip().split('\n')
        if len(output) > 0:
            headers = output[0].split(' | ')
            rows = [row.split(' | ') for row in output[1:]]
        else:
            headers = []
            rows = []
        results[name] = {
            'headers': headers,
            'rows': rows
        }

    print("Results:", results)  # Add this line for debugging

    return jsonify(results)

if __name__ == '__main__':
    app.run(debug=True)
