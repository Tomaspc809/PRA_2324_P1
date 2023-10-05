#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T>{
	private:
		Node<T>* first;
		int n;

	public:
		ListLinked(){
			first = nullptr;
			n = 0;
		}
		~ListLinked(){
			Node<T>* aux = first.next;

			for (int i = 0; i < n; i++){
				delete first;
				first = aux;
				aux->next;
			}
		}

		T operator[](int pos){
			return get(pos);
		}
		friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
			out<<"La lista contiene: "<<std::endl;
			Node<T>* aux = list.first;
			
			for (int i = 0; i < list.size(); i++){
				out<<aux.data<<std::endl;
				aux->next;
			}
			return out;
		}

		void insert(int pos, T e) override{
			if (pos < 0 || pos > n){
				throw std::out_of_range("Posición inválida.");
			}
			Node<T> ins = new Node(e);
			Node<T>* aux = first;
			Node<T>* prevaux = nullptr;

			for (int i = 0; i <= pos; i++){
				prevaux = aux;
				aux->next;
			}
			ins.next = aux;

			if (pos == 0){
				first = ins;
			}else{
				prevaux.next = ins;
			}
			n++;
		}
		void append(T e) override{
			Node<T> ins = new Node(e);
			Node<T>* aux = first;

			for (int i = 0; i < n; i++){
				aux->next;
			}
			aux.next = ins;
			n++;
		}
		void prepend(T e) override{
			Node<T> ins = new Node(e);
			ins.next = first;
			first = ins;
			n++;
		}
		T remove(int pos) override{
			if (pos < 0 || pos >= n){
				throw std::out_of_range("Posición inválida.");
			}
			T ret;
			Node<T>* aux = first.next;
			Node<T>* prevaux = first;

			if (pos == 0){
				ret = prevaux.data;
				delete prevaux;
				first = aux;
				n--;
				return ret;
			}
			for (int i = 0; i <= pos; i++){
				prevaux = aux;
				aux->next;
			}
			ret = aux.data;
			prevaux.next = aux.next;
			delete aux;
			n--;
			return ret;
		}
		T get(int pos) override{
			if (pos < 0 || pos >= n){
				throw std::out_of_range("Posición inválida.");
			}
			Node<T>* aux = first;

			for(int i = 0; i < pos; i++){
				aux->next;
			}
			return aux.data;
		}
		int search(T e) override{
			Node<T>* aux = first;

			for(int i = 0; i < n; i++){
				if (e == aux.data){
					return i;
				}
				aux->next;
			}
			return -1;
		}
		bool empty() override{
			if (n == 0){
				return 1;
			}
			return 0;
		}
		int size() override{
			return n;
		}
};
