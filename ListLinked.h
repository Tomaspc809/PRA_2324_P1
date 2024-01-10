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
			this->first = nullptr;
			this->n = 0;
		}
		~ListLinked(){
			Node<T>* aux = first;

			for (int i = 1; i < n; i++){
				first = first->next;
				delete aux;
				aux = first;
			}
			delete first;
		}

		T operator[](int pos){
			return get(pos);
		}
		friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
			out<<"La lista contiene: "<<std::endl;
			Node<T>* aux = list.first;
			T valor;
			for (int i = 0; i < list.n; i++){
				valor = aux->data;
				out<<valor<<std::endl;
				aux = aux->next;
			}
			return out;
		}

		void insert(int pos, T e) override{
			if (pos < 0 || pos > n){
				throw std::out_of_range("Posición inválida.");
			}
			Node<T>* ins;
			Node<T>* aux;

			if(pos == 0){
				first = new Node<T>(e, first);
			}else{
				aux = first;
				
				for(int i = 1; i < pos; i++){
					aux = aux->next;
				}

				ins = new Node<T>(e, aux->next);
				aux->next = ins;
			}
			n++;
		}
		void append(T e) override{
			Node<T>* ins = new Node(e);
			Node<T>* aux = first;

			for (int i = 1; i < n; i++){
				aux = aux->next;
			}
			aux->next = ins;
			n++;
		}
		void prepend(T e) override{
			Node<T>* ins = new Node(e);
			ins->next = first;
			first = ins;
			n++;
		}
		T remove(int pos) override{
			if (pos < 0 || pos >= n){
				throw std::out_of_range("Posición inválida.");
			}
			T ret;
			Node<T>* prev = first;

			if (pos == 0){
				first = first->next;
				ret = prev->data;
				delete prev;
				n--;

				return ret;
			}

			Node<T>* aux = first->next;

			for (int i = 1; i < pos; i++){
				prev = aux;
				aux = aux->next;
			}
			ret = aux->data;
			prev->next = aux->next;
			delete aux;
			n--;

			return ret;
		}
		T get(int pos) const override{
			if (pos < 0 || pos >= n){
				throw std::out_of_range("Posición inválida.");
			}
			Node<T>* aux = first;

			for(int i = 0; i < pos; i++){
				aux = aux->next;
			}

			return aux->data;
		}
		int search(T e) override{
			Node<T>* aux = first;

			for(int i = 0; i < n; i++){
				if (e == aux->data){
					return i;
				}
				aux = aux->next;
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
