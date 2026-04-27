#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ----------- FUNCIONES -----------
double calcularSubtotal(int cantidad, double precio) {
    return cantidad * precio;
}

double calcularDescuento(double subtotal, int tipoPago) {
    double descuento = 0;

    if (subtotal >= 500) {
        descuento += subtotal * 0.05;
    }

    if (tipoPago == 1 && subtotal >= 300) {
        descuento += subtotal * 0.02;
    }

    return descuento;
}

double calcularTotal(double subtotal, double descuento) {
    return subtotal - descuento;
}

// ----------- PROCEDIMIENTOS -----------
void mostrarMenu() {
    cout << "\n===== MENU PRINCIPAL =====\n";
    cout << "1. Registrar venta\n";
    cout << "2. Mostrar todas las ventas\n";
    cout << "3. Generar reporte\n";
    cout << "4. Buscar ventas por monto\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opcion: ";
}

string obtenerTipoPagoTexto(int tipoPago) {
    switch (tipoPago) {
        case 1: return "Efectivo";
        case 2: return "Tarjeta";
        case 3: return "Transferencia";
        default: return "Desconocido";
    }
}

void registrarVenta() {
    ofstream archivo("ventas.txt", ios::app);

    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    string cliente, producto;
    int cantidad, tipoPago;
    double precio;

    cin.ignore();

    cout << "Nombre del cliente: ";
    getline(cin, cliente);

    cout << "Nombre del producto: ";
    getline(cin, producto);

    // Validar cantidad
    while (true) {
        cout << "Cantidad: ";
        cin >> cantidad;
        if (cantidad <= 0) {
            cout << "Error: La cantidad debe ser mayor que 0.\n";
            continue;
        }
        break;
    }

    // Validar precio
    while (true) {
        cout << "Precio unitario: ";
        cin >> precio;
        if (precio <= 0) {
            cout << "Error: El precio debe ser mayor que 0.\n";
            continue;
        }
        break;
    }

    // Validar tipo de pago
    while (true) {
        cout << "Tipo de pago (1=Efectivo, 2=Tarjeta, 3=Transferencia): ";
        cin >> tipoPago;
        if (tipoPago < 1 || tipoPago > 3) {
            cout << "Error: Tipo de pago invalido.\n";
            continue;
        }
        break;
    }

    double subtotal = calcularSubtotal(cantidad, precio);
    double descuento = calcularDescuento(subtotal, tipoPago);
    double total = calcularTotal(subtotal, descuento);

    archivo << cliente << "," << producto << "," << cantidad << "," 
            << precio << "," << subtotal << "," << descuento << "," 
            << total << "," << obtenerTipoPagoTexto(tipoPago) << "\n";

    archivo.close();

    cout << "Venta registrada exitosamente.\n";
}

void mostrarVentas() {
    ifstream archivo("ventas.txt");

    if (!archivo) {
        cout << "No hay ventas registradas.\n";
        return;
    }

    string linea;

    cout << "\n=== LISTADO DE VENTAS ===\n";

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

void generarReporte() {
    ifstream archivo("ventas.txt");

    if (!archivo) {
        cout << "No hay datos para el reporte.\n";
        return;
    }

    string cliente, producto, tipoPagoTexto;
    int cantidad;
    double precio, subtotal, descuento, total;

    int totalVentas = 0;
    double sumaTotal = 0;
    int efectivo = 0, tarjeta = 0, transferencia = 0, conDescuento = 0;

    while (archivo >> cliente) {
        archivo.ignore();
        getline(archivo, producto, ',');
        archivo >> cantidad;
        archivo.ignore();
        archivo >> precio;
        archivo.ignore();
        archivo >> subtotal;
        archivo.ignore();
        archivo >> descuento;
        archivo.ignore();
        archivo >> total;
        archivo.ignore();
        getline(archivo, tipoPagoTexto);

        totalVentas++;
        sumaTotal += total;

        if (tipoPagoTexto == "Efectivo") efectivo++;
        else if (tipoPagoTexto == "Tarjeta") tarjeta++;
        else if (tipoPagoTexto == "Transferencia") transferencia++;

        if (descuento > 0) conDescuento++;
    }

    archivo.close();

    double promedio = (totalVentas > 0) ? (sumaTotal / totalVentas) : 0;

    cout << "\n=== REPORTE GENERAL ===\n";
    cout << "Total de ventas: " << totalVentas << endl;
    cout << "Suma total vendida: Q" << sumaTotal << endl;
    cout << "Promedio de venta: Q" << promedio << endl;
    cout << "Ventas en efectivo: " << efectivo << endl;
    cout << "Ventas con tarjeta: " << tarjeta << endl;
    cout << "Ventas por transferencia: " << transferencia << endl;
    cout << "Ventas con descuento: " << conDescuento << endl;
}

void buscarPorMonto() {
    ifstream archivo("ventas.txt");

    if (!archivo) {
        cout << "No hay datos disponibles.\n";
        return;
    }

 double monto;
    cout << "Ingrese el monto minimo a buscar: Q";
    cin >> monto;

    string linea;
    string cliente, producto, tipoPagoTexto;
    int cantidad;
    double precio, subtotal, descuento, total;

    cout << "\n=== VENTAS ENCONTRADAS ===\n";

    while (archivo >> cliente) {
        archivo.ignore();
        getline(archivo, producto, ',');
        archivo >> cantidad;
        archivo.ignore();
        archivo >> precio;
        archivo.ignore();
        archivo >> subtotal;
        archivo.ignore();
        archivo >> descuento;
        archivo.ignore();
        archivo >> total;
        archivo.ignore();
        getline(archivo, tipoPagoTexto);

        if (total >= monto) {
            cout << cliente << "," << producto << "," << cantidad << ","
                 << precio << "," << subtotal << "," << descuento << ","
                 << total << "," << tipoPagoTexto << endl;
        }
    }

    archivo.close();
}

// ----------- MAIN -----------
int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                registrarVenta();
                break;
            case 2:
                mostrarVentas();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                buscarPorMonto();
                break;
            case 5:
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);
    cout <<"Rodrigo Adrian Barrios Monterosoo" ;

    return 0;
}