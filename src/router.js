const express = require('express');
const SensorController = require('./controller/SensorController');

const router = express.Router();

router.post('/store-sensor-data', SensorController.store);

module.exports = router;