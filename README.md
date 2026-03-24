# 🀄 Jogo de Dominó - MVC

Uma implementação robusta do clássico jogo de dominó desenvolvida em C++, utilizando o padrão de arquitetura **MVC (Model-View-Controller)**.

### 🏗️ Arquitetura
O projeto preza pela separação de responsabilidades para garantir um código escalável:
* **Model:** Gerencia a lógica do jogo e o estado das peças.
* **View:** Responsável pela interface e interação com o usuário.
* **Controller:** Faz a ponte entre os dados e a interface, controlando o fluxo da partida.

### 🛠️ Tecnologias
* C++ Standard
* Arquitetura MVC

### 🏁 Como Executar
1. Tenha um compilador C++ instalado (como o `g++`).
2. Compile todos os arquivos:
   ```bash
   g++ Dom_PROJETO.cpp Dom_Controller.cpp Dom_Model.cpp Dom_View.cpp -o jogo_domino
