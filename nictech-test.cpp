#include <iostream>
#include <fstream>
#include <sstream>

const int MAX_CUSTOMERS = 100;

// Función de utilidad y portable para detener la ejecución
void pauseConsole() 
{
    std::cout << "Presione Enter para continuar..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

// Función de utilidad y portable para limpiar la consola
void clearConsole() 
{
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32) || defined(WIN64)
        system("cls");
    #endif
}

//Estructura que representa a un Customer (Clientes)):
typedef struct 
{
    int code;
    std::string name;
    std::string surname;
    std::string address;
} TCustomer;

// Estructura de la lista de clientes: 
typedef struct  
{
    /**
     * Esta es la declaración de campo/variable miembro de un arreglo de 
     * clientes con la cantidad definida en una constante global que vamos a definir
     * al principio del código.
     **/ 
    TCustomer customers[MAX_CUSTOMERS];
    /**
     *Este es el contador que representa al número de clientes
     * en memoria.
     */
    int numCustomers;
} TCustomerList;

// Funciones para manipular clientes
void showMenu() 
{
    std::cout << "----- MENÚ -----" << std::endl;
    std::cout << "1. Dar de alta un cliente" << std::endl;
    std::cout << "2. Dar de baja un cliente" << std::endl;
    std::cout << "3. Modificar un cliente" << std::endl;
    std::cout << "4. Listar todos los clientes" << std::endl;
    std::cout << "5. Buscar un cliente por código" << std::endl;
    std::cout << "6. Salir" << std::endl;
    std::cout << "Ingrese una opción: ";
}

void create(TCustomerList& customerList) 
{
    clearConsole();
    if (customerList.numCustomers >= MAX_CUSTOMERS) 
    {
        std::cout << "No se pueden agregar más clientes." << std::endl;
        return;
    }

    TCustomer newCustomer;
    
    if (customerList.numCustomers > 0) 
    {
        newCustomer.code = customerList.customers[customerList.numCustomers - 1].code + 1;
    } else 
    {
        newCustomer.code = 100; // Comienza en 100 si es el primer cliente
    }
    
    std::cout << "Ingrese el nombre del cliente: ";
    std::cin >> newCustomer.name;

    std::cout << "Ingrese el apellido del cliente: ";
    std::cin >> newCustomer.surname;

    std::cout << "Ingrese la dirección del cliente: ";
    std::cin.ignore();
    std::getline(std::cin, newCustomer.address);

    customerList.customers[customerList.numCustomers] = newCustomer;
    customerList.numCustomers++;

    std::cout << "Cliente agregado correctamente." << std::endl;
}

void remove(TCustomerList& customerList) 
{
    clearConsole();
    int code;
    std::cout << "Ingrese el código del cliente a dar de baja: ";
    std::cin >> code;

    int position = -1;
    for (int i = 0; i < customerList.numCustomers; i++) 
    {
        if (customerList.customers[i].code == code) 
        {
            position = i;
            break;
        }
    }

    if (position != -1) 
    {
        for (int i = position; i < customerList.numCustomers - 1; i++) 
        {
            customerList.customers[i] = customerList.customers[i + 1];
        }
        customerList.numCustomers--;
        std::cout << "Cliente eliminado correctamente." << std::endl;
    } 
    else 
    {
        std::cout << "Cliente no encontrado." << std::endl;
    }
    pauseConsole();
}

void update(TCustomerList& customerList) 
{
    clearConsole();
    int code;
    std::cout << "Ingrese el código del cliente a modificar: ";
    std::cin >> code;

    int position = -1;
    for (int i = 0; i < customerList.numCustomers; i++) 
    {
        if (customerList.customers[i].code == code) 
        {
            position = i;
            break;
        }
    }

    if (position != -1) 
    {
        std::cout << "Cliente encontrado:" << std::endl;
        std::cout << "Código: " << customerList.customers[position].code << std::endl;
        std::cout << "Nombre: " << customerList.customers[position].name << std::endl;
        std::cout << "Apellido: " << customerList.customers[position].surname << std::endl;
        std::cout << "Dirección: " << customerList.customers[position].address << std::endl;

        std::cout << "Ingrese el nuevo nombre del cliente: ";
        std::cin >> customerList.customers[position].name;

        std::cout << "Ingrese el nuevo apellido del cliente: ";
        std::cin >> customerList.customers[position].surname;

        std::cout << "Ingrese la nueva dirección del cliente: ";
        std::cin.ignore();
        std::getline(std::cin, customerList.customers[position].address);

        std::cout << "Cliente modificado correctamente." << std::endl;
    } 
    else 
    {
        std::cout << "Cliente no encontrado." << std::endl;
    }
    pauseConsole();
}

void read(const TCustomerList& customerList) 
{
    clearConsole();
    
    if (customerList.numCustomers == 0) 
    {
        std::cout << "No hay clientes cargados." << std::endl;
        return;
    }

    for (int i = 0; i < customerList.numCustomers; i++) 
    {
        std::cout << "Código: " << customerList.customers[i].code << std::endl;
        std::cout << "Nombre: " << customerList.customers[i].name << std::endl;
        std::cout << "Apellido: " << customerList.customers[i].surname << std::endl;
        std::cout << "Dirección: " << customerList.customers[i].address << std::endl;
        std::cout << "-------------------" << std::endl;
    }
    pauseConsole();
}

void find(const TCustomerList& customerList) 
{
    clearConsole();
    int code;
    std::cout << "Ingrese el código del cliente a buscar: ";
    std::cin >> code;

    int position = -1;
    for (int i = 0; i < customerList.numCustomers; i++) 
    {
        if (customerList.customers[i].code == code) 
        {
            position = i;
            break;
        }
    }

    if (position != -1) 
    {
        std::cout << "Cliente encontrado:" << std::endl;
        std::cout << "Código: " << customerList.customers[position].code << std::endl;
        std::cout << "Nombre: " << customerList.customers[position].name << std::endl;
        std::cout << "Apellido: " << customerList.customers[position].surname << std::endl;
        std::cout << "Dirección: " << customerList.customers[position].address << std::endl;
    } 
    else 
    {
        std::cout << "Cliente no encontrado." << std::endl;
    }
    pauseConsole();
}

void save(const TCustomerList& customerList) 
{
    clearConsole();
    std::ofstream file("customers.csv");
    if (file.is_open()) {
        for (int i = 0; i < customerList.numCustomers; i++) 
        {
            file << customerList.customers[i].code << "," << customerList.customers[i].name << ","
                 << customerList.customers[i].surname << "," << customerList.customers[i].address << std::endl;
        }
        file.close();
        std::cout << "Clientes guardados en el archivo customers.csv." << std::endl;
    } 
    else 
    {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }
    pauseConsole();
}

void loadCustomersFromFile(TCustomerList& customerList) 
{
    /**
     * @brief abrir el archivo csv para lectura.
     */
    std::ifstream file("customers.csv");
    
    /**
     * @brief si el archivo fue abierto correctamente ejecuta la función.
     */
    if (file.is_open()) 
    {
        /**
         * @brief declaro una variable string linea, 
         * que representa una fila del archivo
         */
        std::string linea;

        /**
         * @brief inicio el ciclo while por cada 
         * línea que tenga el archivo, uso la función
         * getline para poder obtenerlas.
         */
        while (std::getline(file, linea)) 
        {
            //defino el flujo de cadena, para poder procesarlo después.
            std::istringstream iss(linea);
            std::string field;

            std::getline(iss, field, ',');
            customerList.customers[customerList.numCustomers].code = std::stoi(field);

            std::getline(iss, field, ',');
            customerList.customers[customerList.numCustomers].name = field;
            
            std::getline(iss, field, ',');
            customerList.customers[customerList.numCustomers].surname = field;
            
            std::getline(iss, field, ',');
            customerList.customers[customerList.numCustomers].address = field;

            customerList.numCustomers++;
        }
        file.close();
    } 
    else 
    {
        std::cout << "No se pudo abrir el archivo." << std::endl;
    }
}

int main() 
{
    //Estoy definiendo una variable del tipo estructura TCustomerList
    TCustomerList customerList;
    
    //Inicialización (definición) de numCustomers
    customerList.numCustomers = 0; 
    
    /**Cargando desde el archivo (base de datos)
     * con la función loadCustomersFromFile en mi customerList
     * en la misma función se incrementa el contador 
     * que usamos en todo el programa.
    */
    loadCustomersFromFile(customerList);
    
    // A fines prácticos se imprime por pantalla el número de clientes cargados:
    std::cout << "Clientes cargados: " << customerList.numCustomers << std::endl;
    
    //Acá empieza el bucle de Menú con las funcionalidades de todo el programa:
    int option;
    do{
        showMenu();
        std::cin >> option;

        switch (option) 
        {
            case 1:
                create(customerList);
                clearConsole();
                break;
            case 2:
                remove(customerList);
                break;
            case 3:
                update(customerList);
                break;
            case 4:
                read(customerList);
                break;
            case 5:
                find(customerList);
                break;
            case 6:
                save(customerList);
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (option != 6);

    return 0;
}
