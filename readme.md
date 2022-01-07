
# Trabalho SSC0140 - Sistemas Operacionais I (2021-2)

## Alunos
  
- Bruno Germano do Nascimento - 10893131
- Matheus Vieira Gonçalves - 11200397
- Pedro Henrique Dias Junqueira de Souza - 11294312
- Tarcídio Antônio Júnior - 10748347

## Explicações
  
### Como funciona o jogo

O jogo é uma simulação de uma loja de cookies com interface no terminal. O objetivo do jogo é chegar a um número específico de cookies acumulados, competindo com a chegada clientes na loja, que consomem os cookies disponíveis. Caso não haja mais cookies, o consumo será imediatado a sua produção.

Para produzir os cookies, o jogador pode pressionar espaço ou utilizar seus cozinheiros que os assam nos fornos. Cada funcionário leva um tempo para preparar os cookies e logo em seguida os leva em um dos fornos disponíveis. Se não houverem fornos disponíveis, o funcionário espera até que um esteja livre para então descansar. Os cozinheiros não podem fazer nada enquanto esperam. Os funcionários e os fornos realizam esses procedimentos por conta própria, mas, o jogador deve usar os cookies acumulados para contratar mais cozinheiros, comprar mais fornos e aprimorar sua produção, agindo como gerente da loja de cookies.

### Uso de threads e semáforos no jogo

Os processos de preparar  e assar cookies levam um certo tempo, mas, podem ser executados de forma paralela (ou concorrentemente, a depender do número de núcleos do processador usado para executar o jogo), pois cada funcionário e cada forno contam com suas próprias threads, assim como os consumidores de cookies.
Todas essas threads modificam a pontuação (número de cookies) do jogador, que é protegida por um mutex, para evitar a incoerência no valor total, sincronizando as operações. Além disso, um funcionário não pode assar cookies a não ser que exista um forno disponível que comporte o número de cookies preparados. O uso de estados nos fornos age como uma espécie de semáforo implícito, impedindo que mais de uma ação seja executada em um forno por vez.

O jogo também fornece uma visualização clara de como se comportam aplicações multithreads com a adição de mais recursos.

### Especificações

Toda vez que uma thread é criada é somado 1 em um contador atômico e, cada vez que uma thread se encerra, subtrai-se 1 do mesmo contador, dessa forma, no final da execução, o programa testa se o contador chegou a 0 e, caso não tenha chegado, espera até que cada uma das threads se encerre.

No total, somam-se 12 threads

- 1 thread responsável por escutar entradas do teclado;

- 4 threads, 1 para cada um dos fornos;

- 4 threads, 1 para cada um dos cozinheiros;

- 1 thread responsável por atualizar constantemente a interface gráfica;

- 1 thread geradora de clientes;

- 1 thread responsável por aumentar a quantidade de clientes ao longo do tempo;

Além disso, todos os trechos criticos do código são protegidos por mutexes, isso pode ser observado tanto em partes apenas funcionais quanto em variáveis compartilhadas:

- Na função draw e setup da classe BorderedWindow, como a biblioteca ncurses desenha apenas 1 elemento por vez e como as atualizações podem vir de qualquer lugar (resize do terminal por exemplo), foi necessário adicionar um mutex que impedisse que duas coisas fossem desenhadas simultaneamente, o que resultaria na impressão de lixo;

- A variável que conta o número de cookies é compartilhada em diversos locais do código, sendo assim, para acessá-la, é necessário utilizar um setter que permite que apenas 1 thread altere o valor por vez;

- Quando um funcionário termina de preparar os biscoitos, ele procura o forno que melhor se adequa a quantidade que ele produziu (algoritimo de best fit), mas apenas 1 funcionário pode fazer isso por vez. Para atingir tal funcionalidade foi necessário adicionar um mutex nesse trecho do código, evitando que dois ou mais funcionários utilizassem o mesmo forno;

- Outro mutex foi utilizado para que não fosse possível aumentar a quantidade de clientes por segundo enquanto se cria novos clientes, o que poderia acarretar em erros de leitura/escrita da variável;

OBS: É válido destacar que em diversos momentos os mutexes foram utilizado com o auxilio de lock guards. A partir do momento que se utiliza um lock guard o mutex faz um lock automaticamente e, quando a variável sai do contexto, o mutex realiza seu unlock.

## Como jogar

### Instalação (Linux)

Essa aplicação utiliza a biblioteca [ncurses](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/) para interface gráfica no terminal. Para a instalar, execute o comando

```sudo apt-get install libncurses5-dev libncursesw5-dev```.

Para compilar projeto, com um terminal no diretório raiz do projeto, utilize o comando ```make all```.

### Iniciando o jogo

Para iniciar o jogo, abra um terminal em tela cheia na pasta raiz do projeto e execute o comando ```make run```. O jogo foi testado em telas com resolução 1366x768 e superiores, e pode ser que a interface não funcione corretamente em telas menores.

### Controles

Os controles são feitos inteiramente pelo teclado. As ações só podem ser feitas se o usuário tiver o número mínimo de cookies necessário para cada uma delas, especificado na interface do jogo.

- 1, 2, 3, 4: Comprar e evoluir fornos

- q, w, e, r: Comprar e evoluir funcionários

- Espaço: Produz 1 Cookie

## Observações finais

As palavras funcionários e cozinheiros são usadas como sinônimos ao longo de todo trabalho.
  
### Sobre o ncurses

Note que o ncurses, pelo próprio design da biblioteca, gera alguns vazamentos de memória. [Mais informação pode ser encontrada nesse link.](https://invisible-island.net/ncurses/ncurses.faq.html#config_leaks)