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
    algorithm = data['algorithm']
    context_switch_time = data['contextSwitchTime']
    processes = data['processes']
    
    input_data = f"{len(processes)}\n"
    for process in processes:
        input_data += f"{process['name']} {process['arrivalTime']} {process['burstTime']}\n"
    
    # Print input data for debugging
    print("Input Data:", input_data)
    
    # Save input data to the scheduler directory
    input_file = os.path.join(SCHEDULER_DIR, 'input.txt')
    with open(input_file, 'w') as f:
        f.write(input_data)
    
    # Execute the C++ scheduler from the scheduler directory
    command = f"{os.path.join(SCHEDULER_DIR, 'scheduler')} {algorithm} {context_switch_time} < {input_file}"
    result = subprocess.run(command, shell=True, capture_output=True, text=True, cwd=SCHEDULER_DIR)
    
    # Read the output from the C++ program
    output = result.stdout
    print("Scheduler Output:", output)  # Print the output for debugging

    return jsonify({'output': output})

if __name__ == '__main__':
    app.run(debug=True)
