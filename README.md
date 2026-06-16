# Trabalho: Sistema BeeCare

Integrantes: Raí Rodrigues, Pedro Lima e Lucas Lima

Disciplina: Algoritmos e Programação I

Professora: Dra. Alcilene Dalília de Sousa

## Descrição

O BeeCare é um sistema em linguagem C para cadastro de abelhas sem ferrão e controle de manejo por agenda.

## Funcionalidades

- Cadastrar, listar, buscar, alterar e remover abelhas.
- Cadastrar, listar, buscar por data, buscar por abelha, alterar e remover manejos.
- Monitoramento por sensores.
- Geração de relatórios.
- Validação simples de datas no formato `dd/mm/aaaa`.
- Confirmação antes de exclusões.
- Reorganização dos vetores após remover registros.
- Persistência dos dados em arquivos binários dentro da pasta `database`.

## Arquivos de Dados

Os dados ficam salvos em:

- `database/abelhas.bin`
- `database/agenda.bin`
- `database/sensores.bin`

Caso os arquivos ainda não existam, o sistema cria e salva os dados automaticamente durante o uso.

Os arquivos `.bin` salvam o total de registros e depois os dados das structs. Ao abrir o programa, esses dados voltam para os vetores, permitindo acesso no código como `abelhas[i].nomePopular`, `abelhas[i].regiao`, `manejos[i].data` e assim por diante.

## Compilação

```bash
gcc -I include src/main.c .\functions\* .\jobs\* -o build/BeeTracker
```

No Windows, também pode ser usado:

```bash
gcc -I include src/main.c .\functions\* .\jobs\* -o build/BeeTracker.exe
```

## Execução

Linux/macOS:

```bash
./build/BeeTracker
```

Windows:

```bash
build\BeeTracker.exe
```

## Bugs conhecidos

nenhum bug conhecido
