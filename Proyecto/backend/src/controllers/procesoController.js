const Proceso = require('../models/proceso.js');
const Sequelize = require('sequelize');

// Función para obtener los últimos 50 registros de la tabla procesos
async function obtenerUltimosProcesos(req, res, next) {
    try {
        const ultimosProcesos = await Proceso.findAll({
            limit: 50,
            order: [['fecha_hora_solicitud', 'DESC']] // Ordenados por fecha_hora_solicitud de forma descendente
        });

        res.status(200).json(ultimosProcesos);
    } catch (error) {
        next(error);
    }
}

// Función para obtener el top 10 procesos con más memoria utilizada
async function obtenerTopMemoriaProcesos(req, res, next) {
    try {
        // Obtener la suma total de la memoria
        const memoriaTotal = await Proceso.sum('tamano_segmento');

        // Query para obtener el top 10 procesos con más memoria utilizada
        const topMemoriaProcesos = await Proceso.findAll({
            attributes: [
                'pid',
                'nombre_proceso',
                [Sequelize.literal('SUM(CASE WHEN llamada = "mmap2" THEN tamano_segmento ELSE 0 END) - SUM(CASE WHEN llamada = "munmap" THEN tamano_segmento ELSE 0 END)'), 'memoria'],
            ],
            group: ['pid', 'nombre_proceso'],
            having: Sequelize.literal('SUM(CASE WHEN llamada = "mmap2" THEN tamano_segmento ELSE 0 END) - SUM(CASE WHEN llamada = "munmap" THEN tamano_segmento ELSE 0 END) > 0'),
            order: [[Sequelize.literal('memoria'), 'DESC']],
            limit: 10
        });

        // Calcular el porcentaje de memoria
        const topProcesosConPorcentaje = topMemoriaProcesos.map(proceso => {
            const memoria = proceso.getDataValue('memoria');
            const porcentaje = memoriaTotal ? (memoria / memoriaTotal * 100).toFixed(2) : 0;
            return {
                pid: proceso.pid,
                nombre: proceso.nombre_proceso,
                memoria: memoria,
                porcentaje: porcentaje
            };
        });

        res.status(200).json(topProcesosConPorcentaje);
    } catch (error) {
        next(error);
    }
}

module.exports = {
    obtenerUltimosProcesos,
    obtenerTopMemoriaProcesos
};