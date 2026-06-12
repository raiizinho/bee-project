# Trabalho: Sistema BeeCare

Integrantes: Rai Rodrigues, Pedro Lima e Lucas Lima

Disciplina: Algoritmos e Programacao I

Professora: Dra. Alcilene Dalilia de Sousa

## Descricao

O BeeCare e um sistema em linguagem C para cadastro de abelhas sem ferrao e controle de manejo por agenda.

## MVP

O MVP da BeeCare e um sistema simples para cadastrar abelhas sem ferrao e organizar uma agenda de manejo com datas importantes, como revisoes, alimentacao, limpeza, troca de caixa, divisao de colonia e outras atividades do meliponicultor.

Nesta versao, as rotas de sensores e relatorios aparecem no menu principal, mas ficam reservadas para implementacao do restante do grupo.

## Funcionalidades

- Cadastrar, listar, buscar, alterar e remover abelhas.
- Cadastrar, listar, buscar por data, buscar por abelha, alterar e remover manejos.
- Menus de sensores e relatorios mantidos como espaco para integracao com o grupo.
- Validacao simples de datas no formato `dd/mm/aaaa`.
- Confirmacao antes de exclusoes.
- Reorganizacao dos vetores apos remover registros.
- Persistencia dos dados em arquivos binarios dentro da pasta `database`.

## Arquivos de dados

Os dados ficam salvos em:

- `database/abelhas.bin`
- `database/agenda.bin`

Caso os arquivos ainda nao existam, o sistema cria e salva os dados automaticamente durante o uso.

Os arquivos `.bin` salvam o total de registros e depois os dados das structs. Ao abrir o programa, esses dados voltam para os vetores, permitindo acesso no codigo como `abelhas[i].nomePopular`, `abelhas[i].regiao`, `manejos[i].data` e assim por diante.

## Compilacao

```bash
gcc -I include src/main.c .\functions\* .\jobs\* -o build/beecare
```

No Windows, tambem pode ser usado:

```bash
gcc -I include src/main.c .\functions\* .\jobs\* -o build/beecare.exe
```

## Execução

Linux/macOS:

```bash
./build/beecare
```

Windows:

```bash
build\beecare.exe
```

## Bugs conhecidos

Os menus de sensores e relatorios ainda nao executam operacoes completas, pois foram deixados para integracao com as partes dos outros integrantes.
