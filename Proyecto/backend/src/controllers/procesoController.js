const Proceso = require('../models/proceso.js');

// Función para obtener los últimos 10 registros de la tabla procesos
async function obtenerUltimosProcesos(req, res, next) {
    try {
        const ultimosProcesos = await Proceso.findAll({
            limit: 10,
            order: [['fecha_hora_solicitud', 'DESC']] // Ordenados por fecha_hora_solicitud de forma descendente
        });

        res.status(200).json(ultimosProcesos);
    } catch (error) {
        next(error);
    }
}

module.exports = {
    obtenerUltimosProcesos
};