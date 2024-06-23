const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const cookieParser = require('cookie-parser');
const logger = require('./util/logger');

require('mandatoryenv').load([
    'DB_HOST',
    'DB_DATABASE',
    'DB_USER',
    'DB_PASSWORD',
    'PORT',
    'SECRET'
]);

const { PORT } = process.env;

const app = express();

// Configurar middleware
app.use(express.json({ limit: '50mb' }));
app.use(express.urlencoded({ extended: true, limit: '10mb' }));
app.use(cookieParser());
app.use(cors()); // Aquí se configura el middleware CORS
app.use(helmet());
app.use(logger.dev, logger.combined);

// Middleware para establecer el tipo de contenido JSON en cada respuesta
app.use('*', (req, res, next) => {
    res.setHeader('Content-Type', 'application/json');
    next();
});

// Rutas
app.use('/', require('./routes/router.js'));

// Manejar errores
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({
        status: false,
        message: 'Internal Server Error'
    });
});

// Manejar ruta no válida
app.use('*', (req, res) => {
    res.status(404).json({
        status: false,
        message: 'Endpoint Not Found'
    });
});

// Iniciar servidor
app.listen(PORT, () => {
    console.info('Server listening on port ', PORT);
});
