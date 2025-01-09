const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();

// Middleware
app.use(cors());
app.use(bodyParser.json());

// data
let checkins = [];
const userNames = {
    "1D183809101D04E0": "Tuan A",
    "5CC43709101D04E0": "Tuan B",
    // ...
};
function formatTimestamp() {
    const now = new Date();

    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');

    const day = String(now.getDate()).padStart(2, '0');
    const month = String(now.getMonth() + 1).padStart(2, '0'); // Months are 0-based
    const year = String(now.getFullYear()); // Get last two digits of the year

    const time = `${hours}:${minutes}:${seconds}`;
    const date = `${day}/${month}/${year}`;

    const datetime = `${date}  ${time}`;

    return datetime;
}

// API nhận UID
app.post('/api/checkin', (req, res) => {
    const { uid } = req.body;
    if (!uid) {
        return res.status(400).json({ message: "UID is required" });
    }

    const name = userNames[uid] || "Unknown";
    const timestamp = formatTimestamp();

    // Xác định trạng thái ra vào
    const occurrence = checkins.filter(entry => entry.uid === uid).length;
    const status = (occurrence % 2 === 0) ? "VÀO" : "RA";

    checkins.push({ uid, name, timestamp, status });

    console.log(`UID received: ${uid}, Name: ${name}, Status: ${status} at ${timestamp}`);
    res.json({ message: "Check-in successful", uid, name, status, timestamp });
});

// API lấy danh sách
app.get('/api/checkins', (req, res) => {
    res.json(checkins);
});

// API reset danh sách
app.delete('/api/reset', (req, res) => {
    checkins = [];
    console.log("Check-in list reset.");
    res.json({ message: "Check-in list reset successfully." });
});

// Start server
const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
