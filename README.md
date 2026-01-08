# 🚇Metro Route Planning System (Pune & Mumbai)
A multi-city public transit route planner that computes optimal travel paths across Metro and Local Rail networks using graph algorithms. The system supports interchanges, fare estimation, and travel-time calculation, exposed through a backend API and consumed by a lightweight web interface.
## 📌 Problem Statement
Urban commuters often struggle to:
- Identify the shortest or fastest route

- Understand line interchanges

- Estimate fare and travel time across mixed transit systems
This project addresses these problems by modeling the transit network as a weighted graph and computing optimal routes programmatically.
## 🛠️ Tech Stack
| Layer               | Technology                                               |
| ------------------- | -------------------------------------------------------- |
| Core Routing Engine | **C++**                                                  |
| Algorithm           | **Dijkstra’s Shortest Path Algorithm**                   |
| Backend API         | **FastAPI (Python)**                                     |
| Frontend            | **HTML, CSS, JavaScript**                                |
| Data Model          | Graph (Stations as nodes, connections as weighted edges) |

## ⚙️ System Architecture
User (Browser)
     ↓
Frontend (HTML/CSS/JS)
     ↓  REST API
FastAPI Backend
     ↓
C++ Routing Engine
     ↓
Graph-based Route Computation
## 🧠 Key Features
- ✅ Multi-city support (Pune & Mumbai)

- 🚉 Interchange-aware routing

- ⏱️ Total travel time calculation

- 💳 Dynamic fare estimation

- 🔁 Real-time route recomputation

- 📡 Clean REST APIs for scalability
## 🔍 How It Works
* Each station is modeled as a node
* Each connection is a weighted edge (time cost)
* Dijkstra’s algorithm finds the shortest path
* Route metadata includes:
   * Station sequence
   * Line changes (interchanges)
   * Total time
   * Estimated fare
## 🚀 Getting Started
### 1️⃣ Clone the Repository
```bash
git clone https://github.com/<your-username>/metro-route-planner.git
cd metro-route-planner
```
### 2️⃣ Backend Setup
```bash
pip install fastapi uvicorn
uvicorn main:app --reload
```
### 3️⃣ Run Frontend
```bash
Open index.html in your browser or serve it via a local server.
```
## 📁 Project Structure

```text
├── backend/
│   ├── main.py        # Backend entry point
│   ├── routes.py     # API route definitions
│   └── data/          # Data storage and resources
│
├── core/
│   └── route_engine.cpp  # Core logic (C++ route engine)
│
├── frontend/
│   ├── index.html     # Frontend HTML
│   ├── style.css      # Styling (CSS)
│   └── app.js         # Frontend logic (JavaScript)
│
└── README.md          # Project documentation
```


## 📈 Scalability & Future Improvements
- Add real-time congestion weights

- Support bus + metro hybrid routing

- Integrate map-based visualization
- Add unit tests for routing engine
- Containerize using Docker
## 🎯 Learning Outcomes
- Practical application of graph algorithms
- Backend–frontend integration via REST APIs
- Designing scalable, city-agnostic systems
- Writing clean, modular, and testable code
