#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ================= ESTRUTURAS =================

struct Categoria {
    int codigo;
    string descricao;
};

struct Produto {
    int codigo;
    string descricao;
    int codigo_categoria;
    double preco_unitario;
};

struct Ingrediente {
    int codigo;
    string descricao;
    double quant_estoque;
    double estoque_minimo;
    double estoque_maximo;
    double preco_unitario;
};

struct Cliente {
    int codigo;
    string nome;
    string telefone;
};

struct Garcom {
    int codigo;
    string nome;
};

struct Pedido {
    int codigo;
    int codigo_cliente;
    int codigo_garcom;
    string data;
};

struct ItemPedido {
    int codigo_pedido;
    int codigo_produto;
    int quantidade;
};

struct ConsumoIngrediente {
    int codigo_produto;
    int codigo_ingrediente;
    double quantidade_necessaria;
};

// ================= FUNÇÕES DE BUSCA =================

int buscarCategoria(vector<Categoria>& categorias, int codigo) {
    for (int i = 0; i < categorias.size(); i++) {
        if (categorias[i].codigo == codigo)
            return i;
    }
    return -1;
}

int buscarProduto(vector<Produto>& produtos, int codigo) {
    for (int i = 0; i < produtos.size(); i++) {
        if (produtos[i].codigo == codigo)
            return i;
    }
    return -1;
}

int buscarIngrediente(vector<Ingrediente>& ingredientes, int codigo) {
    for (int i = 0; i < ingredientes.size(); i++) {
        if (ingredientes[i].codigo == codigo)
            return i;
    }
    return -1;
}

int buscarCliente(vector<Cliente>& clientes, int codigo) {
    for (int i = 0; i < clientes.size(); i++) {
        if (clientes[i].codigo == codigo)
            return i;
    }
    return -1;
}

int buscarGarcom(vector<Garcom>& garcons, int codigo) {
    for (int i = 0; i < garcons.size(); i++) {
        if (garcons[i].codigo == codigo)
            return i;
    }
    return -1;
}

int buscarPedido(vector<Pedido>& pedidos, int codigo) {
    for (int i = 0; i < pedidos.size(); i++) {
        if (pedidos[i].codigo == codigo)
            return i;
    }
    return -1;
}

// ================= LEITURA DE DADOS =================

void lerCategorias(vector<Categoria>& categorias) {
    int qtd;

    cout << "\nQuantidade de categorias: ";
    cin >> qtd;

    for (int i = 0; i < qtd; i++) {
        Categoria c;

        cout << "\nCodigo: ";
        cin >> c.codigo;

        cin.ignore();

        cout << "Descricao: ";
        getline(cin, c.descricao);

        categorias.push_back(c);
    }
}

void lerProdutos(vector<Produto>& produtos) {
    int qtd;

    cout << "\nQuantidade de produtos: ";
    cin >> qtd;

    for (int i = 0; i < qtd; i++) {
        Produto p;

        cout << "\nCodigo: ";
        cin >> p.codigo;

        cin.ignore();

        cout << "Descricao: ";
        getline(cin, p.descricao);

        cout << "Codigo da categoria: ";
        cin >> p.codigo_categoria;

        cout << "Preco unitario: ";
        cin >> p.preco_unitario;

        produtos.push_back(p);
    }
}

void lerIngredientes(vector<Ingrediente>& ingredientes) {
    int qtd;

    cout << "\nQuantidade de ingredientes: ";
    cin >> qtd;

    for (int i = 0; i < qtd; i++) {
        Ingrediente ing;

        cout << "\nCodigo: ";
        cin >> ing.codigo;

        cin.ignore();

        cout << "Descricao: ";
        getline(cin, ing.descricao);

        cout << "Quantidade estoque: ";
        cin >> ing.quant_estoque;

        cout << "Estoque minimo: ";
        cin >> ing.estoque_minimo;

        cout << "Estoque maximo: ";
        cin >> ing.estoque_maximo;

        cout << "Preco unitario: ";
        cin >> ing.preco_unitario;

        ingredientes.push_back(ing);
    }
}

// ================= CLIENTES =================

void incluirCliente(vector<Cliente>& clientes) {
    Cliente c;

    cout << "\nCodigo do cliente: ";
    cin >> c.codigo;

    if (buscarCliente(clientes, c.codigo) != -1) {
        cout << "Codigo ja existente!\n";
        return;
    }

    cin.ignore();

    cout << "Nome: ";
    getline(cin, c.nome);

    cout << "Telefone: ";
    getline(cin, c.telefone);

    clientes.push_back(c);

    cout << "Cliente cadastrado!\n";
}

// ================= GARÇONS =================

void incluirGarcom(vector<Garcom>& garcons) {
    Garcom g;

    cout << "\nCodigo do garcom: ";
    cin >> g.codigo;

    if (buscarGarcom(garcons, g.codigo) != -1) {
        cout << "Codigo ja existente!\n";
        return;
    }

    cin.ignore();

    cout << "Nome: ";
    getline(cin, g.nome);

    garcons.push_back(g);

    cout << "Garcom cadastrado!\n";
}

// ================= EXCLUIR PRODUTO =================

void excluirProduto(vector<Produto>& produtos) {
    int codigo;

    cout << "\nCodigo do produto: ";
    cin >> codigo;

    int pos = buscarProduto(produtos, codigo);

    if (pos == -1) {
        cout << "Produto nao encontrado!\n";
        return;
    }

    produtos.erase(produtos.begin() + pos);

    cout << "Produto excluido!\n";
}

// ================= INCLUIR ITEM PEDIDO =================

void incluirProdutoPedido(
    int codigoPedido,
    vector<Produto>& produtos,
    vector<Ingrediente>& ingredientes,
    vector<ConsumoIngrediente>& consumos,
    vector<ItemPedido>& itens
) {
    int codProduto;
    int quantidade;

    cout << "\nCodigo do produto: ";
    cin >> codProduto;

    int posProd = buscarProduto(produtos, codProduto);

    if (posProd == -1) {
        cout << "Produto nao encontrado!\n";
        return;
    }

    cout << "Descricao: " << produtos[posProd].descricao << endl;
    cout << "Preco: R$ " << produtos[posProd].preco_unitario << endl;

    cout << "Quantidade: ";
    cin >> quantidade;

    // Verifica estoque
    for (int i = 0; i < consumos.size(); i++) {
        if (consumos[i].codigo_produto == codProduto) {

            int posIng = buscarIngrediente(
                ingredientes,
                consumos[i].codigo_ingrediente
            );

            double necessario =
                consumos[i].quantidade_necessaria * quantidade;

            cout << "Ingrediente: "
                 << ingredientes[posIng].descricao << endl;

            if (ingredientes[posIng].quant_estoque < necessario) {
                cout << "Estoque insuficiente!\n";
                return;
            }
        }
    }

    // Baixa estoque
    for (int i = 0; i < consumos.size(); i++) {
        if (consumos[i].codigo_produto == codProduto) {

            int posIng = buscarIngrediente(
                ingredientes,
                consumos[i].codigo_ingrediente
            );

            double necessario =
                consumos[i].quantidade_necessaria * quantidade;

            ingredientes[posIng].quant_estoque -= necessario;
        }
    }

    ItemPedido item;

    item.codigo_pedido = codigoPedido;
    item.codigo_produto = codProduto;
    item.quantidade = quantidade;

    itens.push_back(item);

    cout << "Produto incluido no pedido!\n";
}

// ================= NOVO PEDIDO =================

void novoPedido(
    vector<Pedido>& pedidos,
    vector<Cliente>& clientes,
    vector<Garcom>& garcons,
    vector<Produto>& produtos,
    vector<Ingrediente>& ingredientes,
    vector<ConsumoIngrediente>& consumos,
    vector<ItemPedido>& itens
) {
    Pedido p;

    cout << "\nCodigo do pedido: ";
    cin >> p.codigo;

    cout << "Codigo cliente: ";
    cin >> p.codigo_cliente;

    int posCliente = buscarCliente(clientes, p.codigo_cliente);

    if (posCliente == -1) {
        cout << "Cliente nao encontrado!\n";
        return;
    }

    cout << "Cliente: " << clientes[posCliente].nome << endl;

    cout << "Codigo garcom: ";
    cin >> p.codigo_garcom;

    int posGarcom = buscarGarcom(garcons, p.codigo_garcom);

    if (posGarcom == -1) {
        cout << "Garcom nao encontrado!\n";
        return;
    }

    cout << "Garcom: " << garcons[posGarcom].nome << endl;

    cin.ignore();

    cout << "Data: ";
    getline(cin, p.data);

    pedidos.push_back(p);

    incluirProdutoPedido(
        p.codigo,
        produtos,
        ingredientes,
        consumos,
        itens
    );
}

// ================= CONSULTAR INGREDIENTE =================

void consultarIngrediente(vector<Ingrediente>& ingredientes) {
    int codigo;

    cout << "\nCodigo ingrediente: ";
    cin >> codigo;

    int pos = buscarIngrediente(ingredientes, codigo);

    if (pos == -1) {
        cout << "Ingrediente nao encontrado!\n";
        return;
    }

    Ingrediente ing = ingredientes[pos];

    cout << "\nCodigo: " << ing.codigo << endl;
    cout << "Descricao: " << ing.descricao << endl;
    cout << "Quantidade estoque: " << ing.quant_estoque << endl;
    cout << "Estoque minimo: " << ing.estoque_minimo << endl;
    cout << "Estoque maximo: " << ing.estoque_maximo << endl;
    cout << "Preco unitario: R$ " << ing.preco_unitario << endl;

    double total = ing.quant_estoque * ing.preco_unitario;

    cout << "Valor total em estoque: R$ " << total << endl;
}

// ================= ESTOQUE ABAIXO DO MÍNIMO =================

void ingredientesAbaixoMinimo(vector<Ingrediente>& ingredientes) {
    double totalCompra = 0;

    cout << fixed << setprecision(2);

    for (int i = 0; i < ingredientes.size(); i++) {

        if (ingredientes[i].quant_estoque <
            ingredientes[i].estoque_minimo) {

            double qtdComprar =
                ingredientes[i].estoque_maximo -
                ingredientes[i].quant_estoque;

            double valorCompra =
                qtdComprar * ingredientes[i].preco_unitario;

            totalCompra += valorCompra;

            cout << "\nCodigo: " << ingredientes[i].codigo << endl;
            cout << "Descricao: "
                 << ingredientes[i].descricao << endl;

            cout << "Quantidade estoque: "
                 << ingredientes[i].quant_estoque << endl;

            cout << "Estoque maximo: "
                 << ingredientes[i].estoque_maximo << endl;

            cout << "Quantidade comprar: "
                 << qtdComprar << endl;

            cout << "Valor compra: R$ "
                 << valorCompra << endl;
        }
    }

    cout << "\nTOTAL REPOSICAO: R$ "
         << totalCompra << endl;
}

// ================= TOTAL ARRECADADO =================

void totalArrecadado(
    vector<Pedido>& pedidos,
    vector<ItemPedido>& itens,
    vector<Produto>& produtos
) {
    double total = 0;

    for (int i = 0; i < itens.size(); i++) {

        int posProd =
            buscarProduto(produtos, itens[i].codigo_produto);

        if (posProd != -1) {

            double valor =
                itens[i].quantidade *
                produtos[posProd].preco_unitario;

            total += valor;
        }
    }

    cout << fixed << setprecision(2);

    cout << "\nTotal arrecadado: R$ "
         << total << endl;
}

// ================= MAIN =================

int main() {

    vector<Categoria> categorias;
    vector<Produto> produtos;
    vector<Ingrediente> ingredientes;
    vector<Cliente> clientes;
    vector<Garcom> garcons;
    vector<Pedido> pedidos;
    vector<ItemPedido> itens;
    vector<ConsumoIngrediente> consumos;

    // Dados exemplo consumo ingredientes

    consumos.push_back({1, 1, 1});
    consumos.push_back({1, 2, 2});

    int opcao;

    do {

        cout << "\n========= MENU =========\n";
        cout << "1 - Ler categorias\n";
        cout << "2 - Ler produtos\n";
        cout << "3 - Ler ingredientes\n";
        cout << "4 - Incluir cliente\n";
        cout << "5 - Incluir garcom\n";
        cout << "6 - Excluir produto\n";
        cout << "7 - Novo pedido\n";
        cout << "8 - Consultar ingrediente\n";
        cout << "9 - Ingredientes abaixo minimo\n";
        cout << "10 - Total arrecadado\n";
        cout << "0 - Sair\n";

        cout << "\nOpcao: ";
        cin >> opcao;

        switch (opcao) {

        case 1:
            lerCategorias(categorias);
            break;

        case 2:
            lerProdutos(produtos);
            break;

        case 3:
            lerIngredientes(ingredientes);
            break;

        case 4:
            incluirCliente(clientes);
            break;

        case 5:
            incluirGarcom(garcons);
            break;

        case 6:
            excluirProduto(produtos);
            break;

        case 7:
            novoPedido(
                pedidos,
                clientes,
                garcons,
                produtos,
                ingredientes,
                consumos,
                itens
            );
            break;

        case 8:
            consultarIngrediente(ingredientes);
            break;

        case 9:
            ingredientesAbaixoMinimo(ingredientes);
            break;

        case 10:
            totalArrecadado(
                pedidos,
                itens,
                produtos
            );
            break;

        case 0:
            cout << "Encerrando...\n";
            break;

        default:
            cout << "Opcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}
