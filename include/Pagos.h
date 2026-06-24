#pragma once
#include "Fecha.h"

class Pagos{

private:
    int _idPago;
    int _idSocio;
    int _idCuota;
    Fecha _fechaPago;
    float _importe;
    bool _estado;

public:
    Pagos();
    Pagos(int idPago, int idSocio, int idCuota, Fecha fechaPago, float importe, bool estado);

    int getIdPago();
    void setIdPago(int idPago);

    int getIdSocio();
    void setIdSocio(int idSocio);

    int getIdCuota();
    void setIdCuota(int idCuota);

    Fecha getFechaPago();
    void setFechaPago(Fecha fechaPago);

    float getImporte();
    void setImporte(float importe);

    bool getEstado();
    void setEstado(bool estado);

    void mostrar(int fila);

    bool guardar();
    int contarRegistros();
    Pagos leer(int posicion);
    int generarNuevoID();
    void listar();
    void listarOrdenadosPorSocio();
    void listarPorSocio();
    void pagosPorMes();
};
