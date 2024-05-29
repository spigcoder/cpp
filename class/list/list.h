#include<assert.h>
#include<algorithm>
#include<iostream>

namespace spigcoder{
	template<typename T>
	struct ListNode{
		using value_type = T;	
		struct ListNode<T> *_next;
		struct ListNode<T> *_prev;
		value_type _data;
		ListNode(const T x = T())
			: _next(nullptr),
			_prev(nullptr),
			_data(x)
		{}
	};

	//为什么要用这么多的模板，这样子就可以传递不同的模板变量来规定不同的寄存器
	template<typename T, typename Ref, typename Ptr>
	struct ListIterator{
		using Node = ListNode<T>;
		using self = ListIterator<T, Ref, Ptr>;
		Node* _node;
		ListIterator(Node* node)	
		:_node(node)	
		{}

		self& operator++(){
			_node = _node->_next;
			return *this;	
		}

		self operator++(int){
			Node tmp(*this);	
			_node = _node->_next;
			return tmp;
		}

		Ref operator*(){
			return _node->_data;	
		}

		//这种主要适用于list中存放的时自定义类型
		Ptr operator->(){
			return &(operator*());	
		}

		//这里应该用迭代器来进行传参
		bool operator!=(const self& it){
			return it._node != _node;
		}

		bool operator==(const self& it){
			return it._node == _node;
		}

		self& operator--(){
			_node = _node->_prev;	
			return *this;
		}

		self operator--(int){
			Node tmp(*this);
			_node = _node->_prev;	
			return tmp;
		}
	};

	//stl中的list是带头双向循环链表，_head也就是哨兵位节点
	template<typename T>
	class list{
	public:
		using iterator = ListIterator<T, T&, T*>;
		using const_iterator = ListIterator<const T, const T&, const T*>;
		using Node = ListNode<T>;
		void empty_init(const T& _val = T());
		void clear();
		list(const T val = T()){ empty_init(val); }
		~list(){ clear(); delete _head; _head = nullptr; }
		list(list<T>& list1){
			empty_init(); 
			for(const auto& e : list1){
				push_back(e);	
			}
		}
		list<T>& operator=(list<T>& li1){
			//To construct an existing object, first remove the original, and then construct it
			//这样写就必须自己手动释放内存
			//clear();
			//for(const auto& e : li1){
			//	push_back(e);	
			//}
			//这么写不用自己释放内存，交换之后li1出了作用域析构会释放内存
			std::swap(_head, li1._head);
			return *this;
		}
		void swap(ListNode<T>* x, ListNode<T>* y);
		iterator begin() {return iterator(_head->_next); }
		const_iterator begin() const { return iterator(_head->_next); };
		iterator end() { return iterator(_head); };
		const_iterator end() const { return iterator(_head); };
		iterator insert(iterator pos, const T& val);
		iterator erase(iterator pos);
		void push_back(const T& val) { insert(end(), val); }
		void push_front(const T& val) { insert(begin(), val); }
		void pop_back() { erase(--end()); }
		void pop_front() { erase(begin()); }
		void display();

	private:
		Node* _head;
	};
	template<typename T>
	void list<T>::swap(ListNode<T>* x, ListNode<T>* y){
		std::swap(x, y);	
	}

	template<typename T>
	void list<T>::clear(){
		auto it = begin();
		while(it != end()){
			it = erase(it);	
		}	
		_head->_next = _head;
		_head->_prev = _head;
	}

	template<typename T>
	void list<T>::empty_init(const T& _val){
		_head = new Node(_val);
		_head->_next = _head;
		_head->_prev = _head;
	}


	//这里的typename是告诉编译器这是一个类型而不是一个值，在模板参数中涉及typename可以不写
	//但是模板定义的其他部分涉及依赖名称typename通常是必须的
	//依赖名称是指在模板定义或声明中名称依赖于模板参数的名称
	template<typename T>
	typename list<T>::iterator list<T>::insert(iterator pos, const T& val){
		//插入是在pos前面插入一个位置，也就是将pos的位置改为值为val的数
		Node* cur = pos._node;
		Node* prev = cur->_prev;	
		Node* NewNode = new Node(val);
		//prev NewNode cur
		cur->_prev	= NewNode;
		NewNode->_prev = prev;
		NewNode->_next = cur;
		prev->_next = NewNode;
		//这里的插入操作不会出现迭代器失效因为没有扩容但是为了统一接口还是可以加上
		return NewNode;
	}

	template<typename T>
	typename list<T>::iterator list<T>::erase(iterator pos){
		assert(pos != iterator(_head));
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* next = cur->_next; 
		
		prev->_next = next;
		next->_prev = prev;	
		delete cur;
		//erase还是会出现迭代器失效的问题
		return next;
	}

	template<typename T>
	void list<T>::display(){
		Node* head = _head->_next;	
		while(head != _head){
			std::cout << head->_data << " ";	
			head = head->_next;
		}
		std::cout << std::endl;
	} 

}
