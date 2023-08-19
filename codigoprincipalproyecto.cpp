// PROYECTO FINAL PROGRAMACION II
// ADMINISTRACION FINANCIERA DE CONJUNTOS RESIDENCIALES
// SANTIAGO MARIN HENAO
// 23/05/2023 v5.11

#include <iostream>
#include <locale.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

// Prototipos de funciones
void menu();
void PQRS();
void show_PQRS();
void llenar_gastos(char name[30]);
void show_gastos(char name[30]);
void add_conjunto();
void show_conjuntos();
bool verificar_nombre(char name[30]);
void mostrar_todos();
void eliminar(char name[30]);
void ordenar_conjuntos();

// Registros
struct NEW_PQRS
{
    char message[200];
};

struct gastos
{
    char name[30];
    float amount;
};

struct conjunto
{
    char name[30];
    bool eliminado;
};

// Funci�n principal
int main()
{
    setlocale(LC_ALL, "spanish");
    menu();
    return 0;
}

// Dibujar men� y llamar a otras funciones
void menu()
{
    int opcion;
    system("CLS");

    cout << "\t---------------------------------------------------------" << endl;
    cout << "\t|\t\tMen� de apoyo al usuario\t\t| " << endl;
    cout << "\t| Adminsitraci�n financiera de conjuntos residenciales  | " << endl;
    cout << "\t---------------------------------------------------------\n"
         << endl;
    cout << "\t1. Ingresar nuevo cliente (Conjunto residencial). " << endl;
    cout << "\t2. Eliminar cliente (Conjunto residencial). " << endl;
    cout << "\t3. Ordenar conjuntos." << endl;
    cout << "\t4. Agregar gastos a cliente espec�fico. " << endl;
    cout << "\t5. Visualizar gastos de cliente espec�fico. " << endl;
    cout << "\t6. Visualizar todos los clientes. " << endl;
    cout << "\t7. Visualizar todos los clientes y sus gastos respectivos. " << endl;
    cout << "\t8. Ingresar PQRS (an�nimo). " << endl;
    cout << "\t9. Visualizar PQRS (an�nimo). " << endl;
    cout << "\t0. Salir. " << endl;
    cout << "\n";

    cout << "\tIngrese una opci�n: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion)
    {
    case 1:
        add_conjunto();
        break;
    case 2:
        system("CLS");
        char nombre_eliminar[30];
        cout << "Ingrese el nombre del conjunto a eliminar: " << endl;
        cin.getline(nombre_eliminar, 30);
        eliminar(nombre_eliminar);
        break;
    case 3:
        ordenar_conjuntos();
        break;
    case 4:
        system("CLS");
        char nombre_gastos[30];
        cout << "Ingrese el nombre del conjunto: " << endl;
        cin.getline(nombre_gastos, 30);
        llenar_gastos(nombre_gastos);
        break;
    case 5:
        system("CLS");
        char nombre_mostrar_gastos[30];
        cout << "Ingrese el nombre del conjunto: " << endl;
        cin.getline(nombre_mostrar_gastos, 30);
        show_gastos(nombre_mostrar_gastos);
        break;
    case 6:
        show_conjuntos();
        break;
    case 7:
        mostrar_todos();
        break;
    case 8:
        PQRS();
        break;
    case 9:
        show_PQRS();
        break;
    case 0:
        system("CLS");
        cout << "�Hasta pronto!" << endl;
        exit(0);
        break;
    default:
        system("CLS");
        cout << "Opci�n inv�lida. Por favor, ingrese una opci�n v�lida." << endl;
        break;
    }
    if (opcion != 0)
    {
        cout << "\nPresione una tecla para volver al men�...";
        cin.ignore();
        menu();
    }
}

// Ingresar una nueva PQRS (an�nima)
void PQRS()
{
    FILE *fp;
    NEW_PQRS pqrs;
    char respuesta;
    system("CLS");
    cout << "Ingrese su PQRS: ";
    cin.getline(pqrs.message, 200);
    fp = fopen("pqrs.txt", "ab");
    fwrite(&pqrs, sizeof(NEW_PQRS), 1, fp);
    fclose(fp);
    cout << "\n�Desea ingresar otra PQRS? (S/N): ";
    cin >> respuesta;
    cin.ignore();
    if (respuesta == 'S' || respuesta == 's')
        PQRS();
    else
        menu();
}

// Mostrar las PQRS ingresadas
void show_PQRS()
{
    FILE *fp;
    NEW_PQRS pqrs;
    system("CLS");
    fp = fopen("pqrs.txt", "rb");
    while (fread(&pqrs, sizeof(NEW_PQRS), 1, fp) == 1)
        cout << "\nPQRS: " << pqrs.message << endl;
    fclose(fp);
    cout << "\nPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}

// Llenar gastos para un conjunto residencial
void llenar_gastos(char name[30])
{
    FILE *fp;
    gastos gasto;
    system("CLS");
    fp = fopen("gastos.dat", "ab");
    if (verificar_nombre(name))
    {
        cout << "\nEl conjunto no existe." << endl;
        cout << "\nPresione una tecla para volver al men�...";
        cin.ignore();
        menu();
    }
    else
    {
        strcpy(gasto.name, name);
        cout << "Ingrese el monto del gasto: ";
        cin >> gasto.amount;
        cin.ignore();
        fwrite(&gasto, sizeof(gastos), 1, fp);
        fclose(fp);
        cout << "\nPresione una tecla para volver al men�...";
        cin.ignore();
        menu();
    }
}

// Mostrar los gastos de un conjunto residencial
void show_gastos(char name[30])
{
    FILE *fp;
    gastos gasto;
    int total = 0;
    system("CLS");
    fp = fopen("gastos.dat", "rb");
    if (verificar_nombre(name))
    {
        cout << "\nEl conjunto no existe." << endl;
        cout << "\nPresione una tecla para volver al men�...";
        cin.ignore();
        menu();
    }
    else
    {
        cout << "Nombre: " << name << endl;
        while (fread(&gasto, sizeof(gastos), 1, fp) == 1)
        {
            if (strcmp(gasto.name, name) == 0)
            {
                cout << "Gasto: " << gasto.amount << endl;
                total += gasto.amount;
            }
        }
        cout << "Total de gastos: " << total << endl;
    }
    fclose(fp);
    cout << "\nPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}

// Agregar un nuevo conjunto residencial
void add_conjunto()
{
    conjunto conj;
    FILE *fp;
    system("CLS");
    cout << "Ingrese el nombre del conjunto: ";
    fflush(stdin);
    cin.getline(conj.name, 30);
    if (!verificar_nombre(conj.name))
    {
        cout << "\nEl nombre del conjunto ya existe." << endl;
        cout << "\nPresione una tecla para volver al men�...";
        cin.ignore();
        menu();
    }
    conj.eliminado = false;
    fp = fopen("conjuntos.dat", "ab");
    fwrite(&conj, sizeof(conjunto), 1, fp);
    fclose(fp);
    cout << "\nConjunto residencial agregado exitosamente." << endl;
    cout << "\nPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}

// Mostrar todos los conjuntos residenciales
void show_conjuntos()
{
    FILE *fp;
    conjunto conj;
    system("CLS");
    fp = fopen("conjuntos.dat", "rb");
    while (fread(&conj, sizeof(conjunto), 1, fp) == 1)
    {
        if (!conj.eliminado)
            cout << "\nConjunto: " << conj.name << endl;
    }
    fclose(fp);
    cout << "\nPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}

// Verificar si el nombre del conjunto ya existe
bool verificar_nombre(char name[30])
{
    FILE *fp;
    conjunto conj;
    fp = fopen("conjuntos.dat", "rb");
    while (fread(&conj, sizeof(conjunto), 1, fp) == 1)
    {
        if (strcmp(conj.name, name) == 0 && !conj.eliminado)
        {
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}

// Mostrar todos los conjuntos residenciales y sus gastos respectivos
void mostrar_todos()
{
    FILE *fp_conjuntos;
    FILE *fp_gastos;
    conjunto conj;
    gastos gasto;
    int total = 0;
    system("CLS");
    fp_conjuntos = fopen("conjuntos.dat", "rb");
    while (fread(&conj, sizeof(conjunto), 1, fp_conjuntos) == 1)
    {
        if (!conj.eliminado)
        {
            cout << "\nConjunto: " << conj.name << endl;
            fp_gastos = fopen("gastos.dat", "rb");
            while (fread(&gasto, sizeof(gastos), 1, fp_gastos) == 1)
            {
                if (strcmp(gasto.name, conj.name) == 0)
                {
                    cout << "Gasto: " << gasto.amount << endl;
                    total += gasto.amount;
                }
            }
            cout << "Total de gastos: " << total << endl;
            total = 0;
            fclose(fp_gastos);
        }
    }
    fclose(fp_conjuntos);
    cout << "\nPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}

// Eliminar un conjunto residencial
void eliminar(char name[30])
{
    FILE *fp;
    conjunto conj;
    fp = fopen("conjuntos.dat", "rb+");
    if (verificar_nombre(name))
    {
        cout << "\nEl conjunto no existe." << endl;
        cout << "\nPresione una tecla para volver al men�...";
        cin.ignore();
        menu();
    }
    else
    {
        while (fread(&conj, sizeof(conjunto), 1, fp) == 1)
        {
            if (strcmp(conj.name, name) == 0 && !conj.eliminado)
            {
                conj.eliminado = true;
                fseek(fp, ftell(fp) - sizeof(conjunto), 0);
                fwrite(&conj, sizeof(conjunto), 1, fp);
                cout << "\nConjunto residencial eliminado exitosamente." << endl;
                break;
            }
        }
    }
    fclose(fp);
    cout << "\nPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}

// Ordenar conjuntos alfab�ticamente
void ordenar_conjuntos()
{
    FILE *fp;
    conjunto conjuntos[100];
    conjunto temp;
    int n = 0;
    fp = fopen("conjuntos.dat", "rb");
    while (fread(&conjuntos[n], sizeof(conjunto), 1, fp) == 1)
        n++;
    fclose(fp);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(conjuntos[j].name, conjuntos[j + 1].name) > 0)
            {
                temp = conjuntos[j];
                conjuntos[j] = conjuntos[j + 1];
                conjuntos[j + 1] = temp;
            }
        }
    }
    fp = fopen("conjuntos.dat", "wb");
    for (int i = 0; i < n; i++)
        fwrite(&conjuntos[i], sizeof(conjunto), 1, fp);
    fclose(fp);
    cout << "\n\tConjuntos ordenados exitosamente." << endl;
    cout << "\n\tPresione una tecla para volver al men�...";
    cin.ignore();
    menu();
}
