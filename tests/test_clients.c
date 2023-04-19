#include "../unity/src/unity.h"
#include "../Headers/clientes.h"
#include "../Headers/verificacoes.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_verifica_nif(void) {
    struct NodeClientes *headClientes = NULL;
    struct Clientes cliente;
    cliente.nif = 123456789;
    InserirCliente(&headClientes, cliente);
// testa a função VerificaNIF
    TEST_ASSERT_TRUE(VerificaNif(headClientes, 123456789));
    TEST_ASSERT_FALSE(VerificaNif(headClientes, 987654321));
}

void test_adicionar_cliente(void) {
    struct NodeClientes *headClientes = NULL;
    Clientes newCliente = AdicionarCliente(headClientes, "João Teste", "Rua 1", 123456789, 100.0f, "joao_teste", "password");

    TEST_ASSERT_EQUAL_STRING("João Teste", newCliente.nome);
    TEST_ASSERT_EQUAL_STRING("Rua 1", newCliente.morada);
    TEST_ASSERT_EQUAL_INT(123456789, newCliente.nif);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, newCliente.saldo);
    TEST_ASSERT_EQUAL_STRING("joao_teste", newCliente.login);
    TEST_ASSERT_EQUAL_STRING("password", newCliente.password);
}


void test_procura_cliente(void) {
    // Inicializa a lista de Clientes e adiocna alguns clientes á lista
    struct NodeClientes *headClientes = NULL;
    struct Clientes cliente1 = {.nome = "João Teste", .morada = "Rua 1", .nif = 123456789, .saldo = 100.0f, .login = "joao_teste", .password = "password"};
    struct Clientes cliente2 = {.nome = "Maria Teste", .morada = "Rua 2", .nif = 987654321, .saldo = 200.0f, .login = "Maria_teste", .password = "password123"};
    InserirCliente(&headClientes, cliente1);
    InserirCliente(&headClientes, cliente2);

    // Chama a função ProcuraCliente com um nif que existe na lista
    Clientes *foundCliente = ProcuraCliente(headClientes, 123456789);

    // Verifica que o return da função não é NULL e que têm os dados esperados.
    TEST_ASSERT_NOT_NULL(foundCliente);
    TEST_ASSERT_EQUAL_INT(123456789, foundCliente->nif);
    TEST_ASSERT_EQUAL_STRING("João Teste", foundCliente->nome);
}


void test_procura_cliente_inexistente(void) {
    // Inicializa a lista de clientes e adiciona alguns clientes
    struct NodeClientes *headClientes = NULL;
    struct Clientes cliente1 = {.nome = "João Teste", .morada = "Rua 1", .nif = 123456789, .saldo = 100.0f, .login = "joao_teste", .password = "password"};
    struct Clientes cliente2 = {.nome = "Maria Teste", .morada = "Rua 2", .nif = 987654321, .saldo = 200.0f, .login = "Maria_teste", .password = "password123"};
    InserirCliente(&headClientes, cliente1);
    InserirCliente(&headClientes, cliente2);

    // Chama a função ProcuraCliente com um NIF que não existe na lista
    Clientes *notFoundCliente = ProcuraCliente(headClientes, 111222333);

    // Verifica que o return é NULL
    TEST_ASSERT_NULL(notFoundCliente);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_verifica_nif);
    RUN_TEST(test_adicionar_cliente);
    RUN_TEST(test_procura_cliente);
    RUN_TEST(test_procura_cliente_inexistente);

    return UNITY_END();
}
