const router = require('express').Router();
const db = require('../models/database.js'); // Importa la instancia de Sequelize
const procesoController = require('../controllers/procesoController.js');

// You can require and use your routes here ;)
// GET /hello endpoint
router.get('/hello', async(req, res) => {
    try {
        // Prueba de conexión a la base de datos
        await db.authenticate();
        console.log('Connection to the database has been established successfully.');

        // Respuesta con el mensaje de saludo
        res.json({ message: 'Hello, world!' });
    } catch (error) {
        console.error('Unable to connect to the database:', error);
        res.status(500).json({ error: 'Database connection error' });
    }
});


// Endpoint para obtener los últimos 10 registros de la tabla procesos
router.get('/procesos', procesoController.obtenerUltimosProcesos);

module.exports = router;