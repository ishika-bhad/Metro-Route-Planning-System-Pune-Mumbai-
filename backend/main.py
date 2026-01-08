from fastapi import FastAPI, Query, Request
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
import subprocess
import json
import os

app = FastAPI(title="Metro Guide")

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
METRO_BIN = os.path.join(BASE_DIR, "..", "metro_cli.exe")

app.mount("/static", StaticFiles(directory="static"), name="static")
templates = Jinja2Templates(directory="templates")

@app.get("/", response_class=HTMLResponse)
def home(request: Request):
    return templates.TemplateResponse("index.html", {"request": request})

@app.get("/route")
def get_route(src: int = Query(...), dest: int = Query(...)):
    if not os.path.exists(METRO_BIN):
        return {"error": "metro_cli.exe not found"}

    result = subprocess.run(
        [METRO_BIN, str(src), str(dest)],
        capture_output=True,
        text=True
    )

    if result.returncode != 0:
        return {"error": result.stderr}

    return json.loads(result.stdout)

# Station list (must match C++ order)
STATIONS = {
    "Pune": [
        {"id": 0, "name": "PCMC"},
        {"id": 1, "name": "Sant Tukaram Nagar"},
        {"id": 2, "name": "Bhosari"},
        {"id": 3, "name": "Kasarwadi"},
        {"id": 4, "name": "Shivajinagar"},
        {"id": 5, "name": "Civil Court"},
        {"id": 6, "name": "Swargate"},
        {"id": 7, "name": "Vanaz"},
        {"id": 8, "name": "Ideal Colony"},
        {"id": 9, "name": "Nal Stop"},
        {"id": 10, "name": "PMC"},
        {"id": 11, "name": "Ruby Hall Clinic"},
    ],
    "Mumbai": [
        {"id": 12, "name": "Versova"},
        {"id": 13, "name": "Andheri West"},
        {"id": 14, "name": "Ghatkopar"},
        {"id": 15, "name": "Oshiwara"},
        {"id": 16, "name": "Goregaon West"},
        {"id": 17, "name": "Malad West"},
        {"id": 18, "name": "Andheri East"},
        {"id": 19, "name": "Jogeshwari East"},
        {"id": 20, "name": "Goregaon East"},
        {"id": 21, "name": "Malad East"},
        {"id": 22, "name": "Churchgate"},
        {"id": 23, "name": "Dadar (W)"},
        {"id": 24, "name": "Andheri (W)"},
        {"id": 25, "name": "Borivali"},
        {"id": 26, "name": "CSMT"},
        {"id": 27, "name": "Dadar (C)"},
        {"id": 28, "name": "Kurla"},
        {"id": 29, "name": "Thane"},
        {"id": 30, "name": "Wadala"},
        {"id": 31, "name": "Vashi"},
        {"id": 32, "name": "Panvel"},
    ]
}

@app.get("/stations")
def get_stations(city: str):
    return STATIONS.get(city, [])
