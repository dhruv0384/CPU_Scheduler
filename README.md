# Advanced CPU Scheduler with Frontend Visualization

## Project Description
This project is an advanced CPU scheduling simulator that implements and compares multiple scheduling algorithms: First Come First Serve (FCFS), Shortest Job First (SJF), Shortest Remaining Time First (SRTF), and Priority Scheduling. It includes a frontend interface for inputting process details and visualizing the scheduling results, including performance metrics such as waiting time, turnaround time, and CPU utilization.

## How to Run the Project

### Prerequisites
- Python 3.x
- Flask
- Chart.js (included via CDN in the HTML file)
- C++ compiler (g++ or similar)

### Dependencies
- Flask for the backend server
- Chart.js for frontend visualization

### Setup Instructions

#### Clone the repository:
```bash
git clone <repository_url>
cd ACM_CPU_Scheduler
```

### Compile the C++ Scheduler

1. **Navigate to the Scheduler Directory and Compile the C++ Code**

    ```bash
    cd scheduler
    g++ -std=c++11 -o scheduler main.cpp parser.cpp scheduler.cpp
    ```

### Flask Server

1. **Navigate to the Backend Directory**
   ```bash
   cd ../backend
   ```

2. **Create a Virtual Environment**

    ```bash
    python3 -m venv venv
    source venv/bin/activate  # On Windows: venv\Scripts\activate
    ```

3. **Install Required Python Packages**

    ```bash
    pip install Flask
    pip install flask-cors
    ```

4. **Run the Flask Server**

    ```bash
    python app.py
    ```


### Frontend Setup

1. **Open the index.html File Located in the Frontend Directory in Your Preferred Web Browser**

    ```bash
    cd ../frontend
    open index.html  # On Windows: start index.html
    ```

## Internal Working of the Project
### Theory of the Project
The CPU Scheduler project aims to simulate various CPU scheduling algorithms, allowing for a detailed comparison of their performance metrics such as waiting time, turnaround time, and CPU utilization. By implementing and analyzing different scheduling strategies, the project provides insights into how each algorithm manages CPU resources and impacts overall system efficiency. The scheduling algorithms included in this project are:

1. First Serve (FCFS):
  * Non-preemptive algorithm.
  * Processes are executed in the order they arrive.

2. Shortest Job First (SJF):
  * Non-preemptive algorithm.
  * Processes with the shortest burst time are executed first.

3. Shortest Remaining Time First (SRTF):
  * Preemptive version of SJF.
  * Processes with the shortest remaining burst time are executed first, allowing interruption by shorter processes.

4. Priority Scheduling:
  * Can be either preemptive or non-preemptive.
  * Processes are executed based on priority levels; lower numbers indicate higher priority.

### Workflow
1. **User Input:**
  * Users input process details (arrival time, burst time, priority) through the frontend interface.
    
2. **Backend Processing:**
  * The Flask server receives process data and runs the scheduling algorithms.
  * The scheduler algorithms are implemented in C++ for performance.
  * Each algorithm's results are calculated and sent back to the frontend.
    
3. **Frontend Visualization:**
  * The results are displayed in tables.
  * Performance metrics such as average waiting time, turnaround time, and CPU utilization are shown.
  * The most efficient algorithm is highlighted based on these metrics.

## Learning Takeaways from the Project
1. **Deep Understanding of CPU Scheduling Algorithms:** Gained in-depth knowledge of various CPU scheduling techniques and their implementation details.
2. **Integration of Frontend and Backend:** Learned how to integrate a Python backend with a C++ core logic and a web-based frontend.
3. **Visualization:** Acquired skills in using Chart.js for creating dynamic and interactive visual representations of scheduling results.
4. **Full-stack Development:** Improved full-stack development capabilities by combining C++, Python, HTML, CSS, and JavaScript.
5. **Performance Comparison:** Developed the ability to analyze and compare the performance of different algorithms based on empirical data.

## References
* **Operating System Concepts by Silberschatz, Galvin, and Gagne:** For understanding the theoretical background of CPU scheduling algorithms.
* **[Flask Documentation](https://flask.palletsprojects.com/en/3.0.x/):** For setting up and running the Flask web server.
* **[Chart.js Documentation](https://www.chartjs.org/docs/latest/):** For creating charts to visualize scheduling results.
* **[C++ Documentation and Tutorials](https://en.cppreference.com/w/):** For implementing the core scheduling algorithms.
* **[Stack Overflow](https://stackoverflow.com/) and [GitHub](https://github.com/):** For troubleshooting and finding community-driven solutions to common problems.







