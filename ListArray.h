#include <ostream>
#include "List.h"

template <typename T>

class ListArray:public List<T>{
	private:
		T* arr;
		int max;
		int n;
		static const int MINSIZE = 2;
		
		void resize(int newSize){
			T a[newSize];
			for (int i = 0; i < n; i++){
				a[i] = arr[i];
			}
			delete[] arr;
			arr = a;
			max = newSize;
		}
	public:
		ListArray(){
			arr = new T[MINSIZE];
			n = 0;
			max = MINSIZE;
		}
		~ListArray(){
			delete[] arr;
		}

		T operator[](int pos){
			return get(pos);
		}
		friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list){
			out<<"La lista contiene: "<<std::endl;
			for (int i = 0; i < list.n; i++){
				out<<list.arr[i]<<std::endl;
			}
			out<<std::endl;
			return out;
		}

		void insert(int pos, T e) override{
			if (pos < 0 || pos > size()){
				throw std::out_of_range("Posición inválida.");
			}
			if (n == max){
				resize(max + 1);
			}
			for (int i = n; i != pos; i--){
				arr[i] = arr[i - 1];
			}
			arr[pos] = e;
			n++;
		}
		void append(T e) override{
			if (n == max){
				resize(max + 1);
			}
			arr[n] = e;
			n++;
		}
		void prepend(T e) override{
			if (n == max){
				resize(max + 1);
			}
			for (int i = n; i != 0; i--){
				arr[i] = arr[i - 1];
			}
			arr[0] = e;
			n++;
		}
		T remove(int pos) override{
			if (pos < 0 || pos > size() - 1){
				throw std::out_of_range("Posición inválida.");
			}

			T del = arr[pos];
			
			for (int i = pos; i < n - 1; i++){
				arr[i] = arr[i + 1];
			}
			n--;
			resize(max - 1);

			return del;
		}
		T get(int pos) override{
			if (pos < 0 || pos > size()-1){
				throw std::out_of_range("Posición inválida.");
			}
			return arr[pos];
		}
		int search(T e) override{
			bool found = false;
			int i = 0;
			
			do{
				found = (arr[i] == e);
				i++;
			}while(!found || i != n);

			if (found){
				return i - 1;
			}
			return -1;
		}
		bool empty() override{
			if (n == 0){
				return true;
			}
			return false;
		}
		int size() override{
			return n;
		}
};
