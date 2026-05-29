#include <iostream>
#include <string>
using namespace std;

//ESTRUTURAS

struct Categoria{
	int codigo;
	string descricao;
};

struct Produtos{
	int codigo;
	string descricao;
	int codigo_categoria;
	float preco_unitario;
	bool ativo=true;
};

struct Ingredientes{
	int codigo;
	string descricao;
	float quant_estoque; 
	float estoque_minimo;
	float estoque_maximo;
	float preco_unitario;
	
};

struct Clientes{
	int codigo;
	string nome;
	string telefone;
};

struct Garcons{
	int codigo;
	string nome;
};

struct Pedidos{
	int codigo;
	int codigo_cliente;
	int codigo_garcom;
	string data;
	
};

struct Itens_pedido{
	int codigo_pedido;
	int codigo_produto;
	int quantidade;
};

struct Consumo_ingredientes{
	int codigo_produto;
	int codigo_ingrediente;
	float quantidade_necessaria;
};

//Leitura

void lerCategoria(Categoria &c){
	cout<<"\nCodigo: ";
	cin >> c.codigo;
	
	cout<<"\n Descricao: ";
	getline(cin, c.descricao);
}

void lerProdutos(Produtos &p){
	cout<<"\nCodigo: ";
	cin >> p.codigo;
	
	cout<<"\nDescricao: ";
	getline(cin, p.descricao);
	
	cout<<"\nCodigo Categoria: ";
	cin>> p.codigo_categoria;
	
	cout<<"\nPreco Unitario: ";
	cin>> p.preco_unitario;
	
}

void lerIngredientes(Ingredientes &i){
	cout<<"\nCodigo: ";
	cin>>i.codigo;
	
	cin.ignore();
	
	cout<<"\nDescricao: ";
	getline(cin, i.descricao);
	
	cout<<"\nQuantidade Estoque: ";
	cin>>i.quant_estoque;
	
	cout<<"\nEstoque Minimo: ";
	cin>>i.estoque_minimo;
	
	cout<<"\nEstoque Maximo: ";
	cin>>i.estoque_maximo;
	
	cout<<"\nPreco Unitario: ";
	cin>>i.preco_unitario;
	
}

//Buscas

int buscarCliente(Cliente clients[], int qtd, int codigo){
	for(int i=0; i<qtd; i++){
		if(clients[i].codigo==codigo){
			return i;
		}
	}
	return -1;
}



