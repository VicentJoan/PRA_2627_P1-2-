#ifndef LIST_H
#define LIST_H
 template <typename T>   //Convierte List en una plantilla. La T representa cualquier tipo de dato, pudiendo almacenar letras o números.
 class List { //Define la clase de la lista
	 public:    //Indica que los métodos que se declaren, podran ser usados desde fuera de la clase
		 virtual void insert(int pos, T val) = 0;
		 virtual T remove(int pos) = 0;
		 virtual T get(int pos) const = 0;
		 virtual int size() const = 0;
		 virtual ~ List() = default;
		 virtual void append(T val) = 0;
		 virtual void prepend(T val) = 0;
		 virtual bool empty() const = 0;
		 virtual int search(T val) const = 0;
 };
#endif
	
