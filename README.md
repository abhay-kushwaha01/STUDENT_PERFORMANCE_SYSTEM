# Student Performance Analysis System

A professional local web application for managing students, marks, attendance, and performance analysis. The backend is implemented entirely in **C (C99+)** using raw sockets and C file handling. The frontend uses HTML, CSS, and Vanilla JavaScript.

## Technology
- Backend: C99, C standard library, sockets, file handling
- Frontend: HTML5, CSS3, Vanilla JavaScript
- Storage: `.dat` files managed by C
- Server: lightweight HTTP server on `localhost:8080`
- No database, Python, Flask, Node.js, React, PHP, Java, C++, or cloud backend

## Folder structure

```text
StudentPerformanceSystem/
├── backend/
│   ├── main.c
│   ├── server.c/.h
│   ├── router.c/.h
│   ├── student.c/.h
│   ├── marks.c/.h
│   ├── attendance.c/.h
│   ├── analysis.c/.h
│   ├── reports.c/.h
│   ├── file_manager.c/.h
│   └── utils.c/.h
├── frontend/
│   ├── index.html
│   ├── dashboard.html
│   ├── students.html
│   ├── student-profile.html
│   ├── marks.html
│   ├── attendance.html
│   ├── analysis.html
│   ├── reports.html
│   ├── css/style.css
│   └── js/*.js
├── data/
├── reports/
├── Makefile
├── run.bat
└── README.md
```

## Requirements

Windows: MinGW-w64 GCC and VS Code. Linux/macOS: GCC/Clang with POSIX sockets.

## Build on Windows

Open the project folder in VS Code terminal and run:

'''bat
run.bat
'''

The script creates the `build` folder, compiles the C sources, starts the C server, and opens the dashboard automatically.

Then open: 

`http://localhost:8080` (dashboard)

## Build manually in Windows

```bat
gcc backend\*.c -std=c99 -Wall -Wextra -O2 -o student_system.exe -lws2_32
student_system.exe
```

## Build on Linux/macOS

```bash
make
./student_system
```

## Access

The application starts directly on the dashboard. No administrator login, password, session, or sign-out system is required.

## API overview

```text
GET  /api/dashboard
GET  /api/students
GET  /api/students/:id
POST /api/students/add
POST /api/students/update
POST /api/students/delete
GET  /api/marks?student_id=...
POST /api/marks/add
POST /api/marks/update
POST /api/marks/delete
GET  /api/attendance?student_id=...
POST /api/attendance/add
POST /api/attendance/update
GET  /api/analysis/:id
GET  /api/reports/student/:id
GET  /api/reports/class
GET  /api/reports/subject?subject=...
```

## Data storage

The application uses C file handling and binary record files. Demo data is included in the ZIP, and the first startup also creates missing files automatically:

- `data/students.dat`
- `data/marks.dat`
- `data/attendance.dat`

The first run creates missing files and seeds demo records if the files are empty.

## Troubleshooting

### Port already in use
Change `SERVER_PORT` in `backend/server.h` and rebuild.

### Windows socket link error
Make sure MinGW is installed and the build includes `-lws2_32`.

### Browser shows 404
Start `run.bat` from the project folder. The launcher sets the project root before starting the server.

### Fresh demo data
Delete the files in `data/` and restart the server. The first startup will recreate seeded data.

## Limitations

This is designed as a BTech demonstration project. It is not intended as a production-grade internet-facing application. The HTTP parser and binary storage are intentionally lightweight.

## Future improvements

- HTTPS via a dedicated TLS layer
- Secure password hashing using a vetted cryptographic library
- Role-based accounts for teachers and administrators
- Pagination for large datasets
- CSV/PDF export using dedicated libraries
- Audit logging


## Adding Your Own Students
Open **Students** and click **+ Add Student**. Enter the student details. After saving, you can immediately open the student profile and use **+ Add / Edit Marks** and **+ Add / Edit Attendance**. The Analysis page and Student Profile then calculate performance from the C backend and file-based records.

The bundled demo dataset contains 40 realistic-looking student records across four engineering departments, eight subjects, varied marks, attendance levels, grades, and at-risk cases so the dashboard is populated on first run.


## Dashboard data troubleshooting

The dashboard reads all statistics from `GET /api/dashboard` in the C backend. The page now displays a visible error message instead of silently showing blank KPI cards if the backend or JSON response is unavailable.

`run.bat` first stops older `student_system.exe` processes, rebuilds the backend, starts the current executable from the project root, and then opens `/dashboard`.

A fresh project includes 40 demo students, 8 subjects, marks and attendance records.

To restore the original demo data at any time, close the C server and run `reset_demo_data.bat`, then run `run.bat`.
