# Trabalho SSC0140 - Sistemas Operacionais I (2021-2)

## Alunos
- Bruno Germano do Nascimento - 10893131
- Matheus Vieira Gonçalves - 11200397
- Pedro Henrique Dias Junqueira de Souza - 11294312
- Tarcídio Antônio Júnior - 10748347

## Explicações

### Como funciona o jogo

O jogo é uma simulação de uma loja de cookies com interface no terminal. O objetivo do jogo é chegar a um número específico de cookies acumulados, mas, com o tempo, vão chegando clientes na loja, que consomem os cookies disponíveis, e, caso não hajam mais cookies, ficam esperando e consomem os cookies imediatamente após produzidos. 
Para produzir os cookies, o jogador tem funcionários que assam esses cookies nos fornos. Cada funcionário leva um tempo para fazer um cookie e então automaticamente o coloca em um dos fornos disponíveis, e os assa. Se não houverem fornos disponíveis, o funcionário espera um forno estar disponível para assar os cookies, e não pode fazer nada enquanto espera. Os funcionários e os fornos realizam esses procedimentos por conta própria, mas, o jogador deve usar os cookies acumulados para comprar mais funcionários, mais fornos e melhorias tanto para funcionários quanto para fornos, agindo como gerente da loja de cookies.

### Uso de threads e semáforos no jogo

Tanto o processo de fazer quanto o processo de assar cookies levam um certo tempo, mas, podem ser executados em paralelo (ou concorrentemente, a depender do número de núcleos do processador usado para executar o jogo), pois cada funcionário e cada forno contam com suas próprias thread. Além disso, os consumidores que diminuem o número de cookies também tem sua própria thread ao mesmo tempo. Todas essas threads modificam a pontuação (número de cookies) do jogador, que é protegida por um mutex, para evitar a perda de modificações no número de cookies, sincronizando as threads. Além disso, um funcionário não pode assar cookies a não ser que exista um forno comprado, disponível e que comporte o número de cookies feitos. O uso de estados nos fornos age como uma espécie de semáforo implícito, impedindo que mais de uma ação seja executada em um forno por vez. 
O jogo também fornece uma visualização clara de como se comportam aplicações multithreads com a adição de mais recursos.

## Como jogar 

### Instalação (Linux)
Essa aplicação utiliza a biblioteca [ncurses](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/) para interface gráfica no terminal. Para a instalar, execute o comando 
```sudo apt-get install libncurses5-dev libncursesw5-dev```.

Para compilar projeto, com um terminal no diretório raiz do projeto, utilize o comando ```make all```.

### Iniciando o jogo

Para iniciar o jogo, abra um terminal em tela cheia na pasta raiz do projeto e execute o comando ```make run```. O jogo foi testado em telas com resolução 1366x768 e superiores, e pode ser que a interface não funcione corretamente em telas menores.

### Controles
Os controles são feitos inteiramente pelo teclado. As ações só podem ser feitas se o usuário tiver o número mínimo de cookies necessário para cada uma delas, especificado na interface do jogo.

- 1, 2, 3 e 4: Compram e evoluem fornos
- Q, W, E e R: Compram e evoluem funcionários

## Observações finais

### Sobre o ncurses

Note que o ncurses, pelo próprio design da biblioteca, gera alguns vazamentos de memória. [Mais informação pode ser encontrada nesse link.](https://invisible-island.net/ncurses/ncurses.faq.html#config_leaks)