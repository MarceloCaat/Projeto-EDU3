#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usuario.h""
void adicionaFim(Lista *lista, User e)
{
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = e;
  novo->prox = NULL;
  if (lista->inicio == NULL)
  {
    lista->inicio = novo;
  }
  else
  {
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL; pi = pi->prox)
      ;
    pi->prox = novo;
  }
}
void cadastrarUser(Lista *lista) {
    FILE *file = fopen("usuarios.b", "ab"); 
    User novoUsuario;

  // Coletando os dados do produto
    printf("digite o codigo");
    scanf("%d", &novoUsuario.codigo);
    do {
        printf("Digite o nome de usuário (deve ser um e-mail válido): ");
        scanf("%s", novoUsuario.username);
        fflush(stdin);
        if (!verificarEmail(novoUsuario.username)) {
            printf("Nome de usuário inválido ou já registrado. Tente novamente.\n");
        } else {
            break;  // Email válido e não registrado
        }
        
    } 

    while (1);
    printf("Digite a senha: ");
    scanf("%s", novoUsuario.password);
    fflush(stdin);

    fwrite(&novoUsuario, sizeof(User), 1, file); 
  adicionaFim(lista, novoUsuario);
      fclose(file);

  printf("Usuario cadastrado com sucesso!\n");
}
void deletar(Lista *lista, int cod)
{
  if (lista->inicio == NULL)
  {
    printf("Lista vazia\n");
  }
  else
  {
    No *pa = NULL;
    No *pi;
    for (pi = lista->inicio; pi->prox != NULL && pi->dado.codigo != cod; pi = pi->prox)
    {
      pa = pi;
    }
    if (pa == NULL)
    {
      if (pi->dado.codigo == cod)
      {
        lista->inicio = pi->prox;
        free(pi);
      }
      else
      {
        printf("Elemento nao encontrado\n");
      }
    }
    else
    {
      if (pi->dado.codigo == cod)
      {
        pa->prox = pi->prox;
        free(pi);
      }
      else
      {
        printf("Elemento nao encontrado\n");
      }
    }
  }
}
void registrar_usuario() {
    FILE *file = fopen("usuarios.b", "ab"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    User novo_usuario;

    do {
        printf("Digite o nome de usuário (deve ser um e-mail válido): ");
        scanf("%s", novo_usuario.username);
        fflush(stdin);

        if (!verificarEmail(novo_usuario.username)) {
            printf("Nome de usuário inválido ou já registrado. Tente novamente.\n");
        } else {
            break;  // Email válido e não registrado
        }
    } while (1);

    printf("Digite a senha: ");
    scanf("%s", novo_usuario.password);
    fflush(stdin);

    fwrite(&novo_usuario, sizeof(User), 1, file); 
    fclose(file);

    printf("Usuário registrado com sucesso!\n");
}
int verificarEmailExistente(const char *username)
{
  FILE *arquivo = fopen("usuarios.b", "ab");
  if (arquivo == NULL)
  {
    return 0; // Arquivo não existe, então email não está cadastrado
  }
  char linha[80];
  while (fgets(linha, 80, arquivo) != NULL)
  {
    // Remover o caractere de nova linha de fgets
    linha[strcspn(linha, "\n")] = 0;
    if (strcmp(linha, username) == 0)
    {
      fclose(arquivo);
      return 1; // Email já cadastrado
    }
  }
  fclose(arquivo);
  return 0; // Email não encontrado no arquivo
}
int verificarcodigoExistente(const int *codigo)
{
  FILE *arquivo = fopen("usuarios.b", "ab");
  if (arquivo == NULL)
  {
    return 0; // Arquivo não existe, então email não está cadastrado
  }
  char linha[80];
  while (fgets(linha, 80, arquivo) != NULL)
  {
    // Remover o caractere de nova linha de fgets
    linha[strcspn(linha, "\n")] = 0;
    if (strcmp(linha, codigo) == 0)
    {
      fclose(arquivo);
      return 1; // Email já cadastrado
    }
  }
  fclose(arquivo);
  return 0; // Email não encontrado no arquivo
}
int verificarcodigo(const int *codigo)
{
  if (verificarcodigoExistente(codigo))
  {
    return 0; // Email já cadastrado
  }
  return 1; // Email válido
}
int verificarEmail(const char *username)
{
  if (strlen(username) >= 80)
  {
    return 0; // Email muito longo
  }
  char *posArroba = strchr(username, '@');
  if (posArroba == NULL)
  {
    return 0; // Email não contém @
  }
  if (verificarEmailExistente(username))
  {
    return 0; // Email já cadastrado
  }
  return 1; // Email válido
}
int login() {
    FILE *file = fopen("usuarios.b", "rb"); 
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char input_username[80];
    char input_password[80];

    printf("Digite o nome de usuário: ");
    scanf("%s", input_username);
    printf("Digite a senha: ");
    scanf("%s", input_password);

    User usuario;
    while (fread(&usuario, sizeof(User), 1, file)) { 
        if (strcmp(usuario.username, input_username) == 0 && strcmp(usuario.password, input_password) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s.\n", usuario.username);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    printf("Nome de usuário ou senha incorretos.\n");
    return 0;
}
int autenticar_admin() {
    char username[80];
    char password[80];

    printf("Digite o nome de usuário: ");
    scanf("%s", username);
    printf("Digite a senha: ");
    scanf("%s", password);

    if (strcmp(username, "adm") == 0 && strcmp(password, "adm") == 0) {
        return 1;
    } else {
        printf("Credenciais incorretas. Acesso negado.\n");
        return 0;
    }
}