/*
Christopher Fernandez Vivas B82951

El codigo segun las coordenadas que ponga el usuario el mismo dira si el poligono formado
es convexo o no convexo y si es convexo imprimira los angulos internos del mismo
*/


#include <stdio.h> //para entradas y salidas de las coordenadas
#include <string.h> // para funciones de string
#include <math.h> // para operaciones matematicas
#include <stdlib.h>
#include <stdio.h>

//estructura para los vectore osea que tenga punto en x y punto en y
struct coordenada
{
    float x;
    float y;
};

//es necesario saber el angulo interno,se necesitan 3 puntos para poder averiguarlo
//las formulas son las siguientes
float AnguloInterno(struct coordenada punto1,struct coordenada punto2,struct coordenada punto3){
//ahora si que tenemos los 3 puntos podemos empezar a realizar las formulas
//creamos los dos vectores
struct coordenada AB;
struct coordenada BC;
struct coordenada AC;
//hacemos la logica necesaria para el primer vector
AB.x = punto2.x - punto1.x;
AB.y = punto2.y - punto1.y;
//printf("%f AB.x", AB.x);
//printf("\n");
//printf("%f AB.y", AB.y);
//printf("\n");
//logica necesaria para hacer el segundo vector
BC.x = (punto3.x) - (punto2.x);
//printf("%f BC.x", BC.x);
//printf("\n");
BC.y = punto3.y - punto2.y;
//printf("%f BC.y", BC.y);
//printf("\n");
//logica para el tercer vector
//AC.x = punto3.x - punto1.x;
//printf("%f", AC.x);
//printf("\n");
//AC.y = punto3.y - punto1.y;
//printf("%f", AC.y);
//ya tenemos los dos vectores creados a partir de los 3 puntos

float ProductoPunto = (AB.x * BC.x) + (AB.y * BC.y); // ya tenemos nuestro producto punto

//sacamos las magnitudes de ambos vectores


float MAB = sqrt(pow(AB.x , 2) + pow(AB.y ,2)); //magnitud el primer vector
//printf("%f este es el MAB", MAB);
//printf("\n");
float MBC = sqrt(pow(BC.x , 2) + pow(BC.y ,2)); // magnitud del segundo vector
//printf("%f este es el MBC", MBC);
//printf("\n");
//float MAC = sqrt(pow(AC.x , 2) + pow(AC.y ,2));
//printf("%f este es el MAC", MAC);
//printf("\n");
//sacamos formula del coseno del angulo

float coseno = ProductoPunto/(MAB * MBC); //ya aqui tenenemos nuestros coseno
 //float coseno = (pow(MAB , 2)+pow(MAC , 2)-pow(MBC , 2))/(2*MAB*MAC);
 //float coseno = (AB.x*BC.x + AB.y *BC.y) / (sqrt(AB.x*AB.x + BC.y*BC.y)*sqrt(BC.x*BC.x+BC.y*BC.y));
 //printf("el valor del coseno es %f", coseno);
 //printf("\n");




 return acos(coseno) * (180/3.14); //retornamls en grados nuestro angulo interno
};

float Convexo(struct coordenada punto1,struct coordenada punto2,struct coordenada punto3){
    // primero sacamos el producto cruz
    //formula del producto cruz
    float ProductoCruz = (punto2.x - punto1.x) * (punto3.y - punto2.y) - (punto2.y - punto1.y) * (punto3.x - punto2.x);

    return ProductoCruz;

};




int main(int argc, char const *argv[])
{

    char pregunta[5]; //le ponemos 5 porque es la cantidad de letras que tiene la palabra salir
    int valor = 100;
    //ocupamos almacenar todos dichos puntos en un array
    struct coordenada puntos[valor];
     //reservamos en memoria un array de 100 puntos por defecto ,sino tendriamos que usar dinamismo de memoria
    float Angulos[valor]; //se refiere a angulos internos
    float ProductoX[valor]; //se refiere a valores para convexo
    int contador = 0; //nos ayudara a saber cuantas veces guardamos un unto en el array
    for (int i = 0; i < valor; i++)
    {
        printf("Por favor ingresa el valor en X que quieras: \n");
        scanf("%f", &puntos[i].x);
        printf("Por favor ingresa el valor en Y que quieras: \n");
        scanf("%f", &puntos[i].y);
        contador += 1;
        printf("quieres seguir agregando coordenadas , pon salir para salir si ya no quieres agregar mas: \n");
        scanf("%s", pregunta);

        //comparamos la salida en dado caso por si el ususario quere dejar de ingresar numeros
         if (strcmp(pregunta, "salir") != 0)// tenemos la funcion strcmp que compara la variable con los caracteres y devulve cero si son iguales 
        {
            continue;
        }
        else
        {
            break; // salimos bucle si son u=iguales
        }
    }
    
    
    //ahora creamos la funcion que nos hara saber el angulo interno a partir de los puntos
    //ya quen tenemos la funcion tenemos que recorrer todos los puntos e ir almacenando los angulos en el array
    //este bucle de angulos internos y la logica esta super bien
    for (int i = 0; i < contador; i++)
    {
        //ya con estos condicionales nos aseguramos que se cierre el poligono
        if (i == (contador-2))
        {
            Angulos[i] = AnguloInterno(puntos[i],puntos[i+1],puntos[0]); //funciona super bien
            //printf("Los 3 puntos para el angulo son : (%f,%f) y (%f,%f) y (%f,%f) \n" , puntos[i].x, puntos[i].y ,puntos[i+1].x, puntos[i+1].y ,puntos[0].x, puntos[0].y);
            ProductoX[i] = Convexo(puntos[i],puntos[i+1],puntos[0]); //funciona super bien
        }
        //condicion para el ultimo valor del vector y tena que volver a agarrar valores del inicio
        else if (i == (contador-1))
        {
            Angulos[i] = AnguloInterno(puntos[i],puntos[0],puntos[1]); //funciona super bien
            //printf("Los 3 puntos para el angulo son : (%f,%f) y (%f,%f) y (%f,%f) \n" , puntos[i].x, puntos[i].y ,puntos[0].x, puntos[0].y ,puntos[1].x, puntos[1].y);
            ProductoX[i] = Convexo(puntos[i],puntos[0],puntos[1]); //funciona super bien
        }
        
        else // para todos los demas numeros que no es el ulitmo ni el penultim
        {
            Angulos[i] = AnguloInterno(puntos[i],puntos[i+1],puntos[i+2]); //funciona super bien
            ProductoX[i] = Convexo(puntos[i],puntos[i+1],puntos[i+2]); //funciona super bien
            //printf("Los 3 puntos para el angulo son : (%f,%f) y (%f,%f) y (%f,%f) \n" , puntos[i].x, puntos[i].y ,puntos[i+1].x, puntos[i+1].y ,puntos[i+2].x, puntos[i+2].y);
            //printf("Los 3 puntos para el producto crux son son : (%f) y (%f) y (%f) \n" , puntos[i],puntos[i+1],puntos[i+2]);
        }
        
         
    }
    




    //Luego tenemos que verificar si es convexo o no , revisando si hay algun cambio de signo en el array
    int SignoInicial = (ProductoX[0] >= 0) ? 1 : -1; //seteamos el signo inicial de nuestro primer valor
    int CONVEXO = 1; //INICIALIZADA EN 1 como si fuera convexo 
    
    //primera prueba cambio de signo
    for (int i = 0; i < contador; i++)
    {
        int SignoDespues = (ProductoX[i] >= 0) ? 1 : -1;//verifica si el signo siguiente es positivo o negativo

        if (SignoInicial * SignoDespues < 0) // compara ambos signos y si da un valor negativo decimos que hubo cambio de signo
        {   
            CONVEXO = 0; // variable que nos servira luego para verificar que sea convexo
            //printf("hubo cambio de signo , por ende no es convexo");
            break;
        }

        SignoInicial = SignoDespues;   //actualizamos nuestro SignoInicial para seguir con las comparaciones
    }
    
    //segunda prueba angulo interno mayor a 180 grados
    for (int i = 0; i < contador; i++)
    {
        if (Angulos[i] > 180)
        {
            CONVEXO =0;
        }
        //si hay algun angulo interno igual a cero es interseccion
        if (Angulos[i] == 0)
        {
            CONVEXO =0;
        }
        // si hay algun angiulo interno con nan es porque al hacer el arcoseno del coseno dio cero
        if (isnan(Angulos[i]))
        {
            Angulos[i] = 0;
            CONVEXO = 0;
        }

        
        
    }
    
    
    
    //condicionales que sirven para imprimir al usuario los valores ingresados si es convexo 
    if (CONVEXO == 1 & contador >=3) // para ser convexo debe de tener contador >= 3 y la badnera de convexo en 1
    {
        printf("--------------------------------------");
        printf("\n");
        printf("Si es un poligono Convexo \n");
        //para los puntos agregados para el usuario
        for (int i = 0; i < contador; i++)
    {
        
        printf("Los puntos agregados son : (%f,%f) \n" , puntos[i].x, puntos[i].y);
        
    }
    //Para los angulos internos
    printf("\n");
    printf("--------------------------------------");
        for (int i = 0; i < contador; i++)
    {
        printf("\n");
        printf("Los Angulos Internos son : (%f) \n", Angulos[i]);
        
    }
    printf("\n");
    printf("--------------------------------------");

    //para los productos cruz
      for (int i = 0; i < contador; i++)
    {
        printf("\n");
        printf("Los productos cruz  son : (%f) \n" , ProductoX[i]);
        
    }
    printf("\n");
    printf("--------------------------------------");

    }
    else if (contador < 3)
    {
        
         printf("--------------------------------------");
         printf("\n");
        printf("Ingresa 3 o mas puntos para que tu poligono sea valido y se tome en cuenta\n");
        printf("--------------------------------------");
    }
    
    else //este else funciona para cuando los puntos ingresados no forman un poligono convexo
    {
        printf("\n");
        
        printf("Las coordenadas ingresadas con anterioridad no son para un poligono Convexo , por ende son invalidas \n");
        printf("Hay un cambio de signo o alguno de sus angulos internos es mayor a 180 \n");
        printf("--------------------------------------");
    //    for (int i = 0; i < contador; i++)
    //{
    //    printf("\n");
    //    printf("Los productos cruz  son : (%f) \n" , ProductoX[i]);
    //    
    //}
    //    printf("--------------------------------------");
    //for (int i = 0; i < contador; i++)
    //{
    //    printf("\n");
    //    printf("Los Angulos Internos son : (%f) \n", Angulos[i]);
    //    
    //}
    //para los puntos agregados para el usuario
        for (int i = 0; i < contador; i++)
    {
        
        printf("Los puntos agregados son : (%f,%f) \n" , puntos[i].x, puntos[i].y);
        
    }
    

    }

    
    

    return 0;
}
