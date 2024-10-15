### Trabalho_ED1
#### Repositório feito para o primeiro trabalho da disciplina Estrutura de Dados 
<br>

### 1. Objetivo
Empregar os conhecimentos adquiridos sobre estruturas de dados (TAD, listas, pilhas e filas) 
no desenvolvimento de uma aplicação computacional, seguindo um conjunto de 
especificações funcionais e de projeto, assim como boas práticas de programação.
<br>
<br>

### 2. Indicações Gerais
- #### O trabalho deve ser desenvolvido em grupos de até quatro alunos, no máximo, sendo que:
- #####   Cada grupo deverá escolher uma das opções descritas na seção 5.
- #####   Serão aceitos somente trabalhos em linguagem de programação C.
- #####   Data de entrega: 29/outubro (terça-feira), até meia noite.
<br>

### 3. Critérios de Avaliação
#### Os trabalhos serão avaliados de acordo com os seguintes critérios:
- #####  Usabilidade da interface: a interface com o usuário deve ser clara e intuitiva, mesmo que seja via linha de comando, exibindo mensagens claras para o usuário.
- #####  Corretude do programa: o programa deve fazer o que foi especificado.
- #####  Estruturas de dados utilizadas: adequação e eficiência.
- #####  Observação dos “bons modos” da programação: TAD, modularidade do código, documentação interna, indentação, etc.
- #####  A cada dia de atraso, 1 ponto é descontado da nota. Lembrem-se de que (i) a média final dos trabalhos deve ser maior ou igual a 5 para que o aluno seja aprovado e (ii) os trabalhos têm peso 3 na média final.
- #####  O plágio de programas não será tolerado. Quaisquer programas similares terão nota zero, independentemente de qual for o original e qual for a cópia.
<br>

### 4. Entrega do Trabalho
#### A entrega dos trabalhos será na atividade aberta no e-Disciplinas. 
##### Será requerido um arquivo comprimido (RAR, ZIP, etc.), que deverá ser postado por 1 dos membros do grupo no site da disciplina, e deve conter:  
* (a) arquivos de código-fonte do programa, 
* (b) arquivo executável do programa,
* (c) arquivo makefile,
* (d) relatório breve.

 O relatório, de aproximadamente 5 páginas, deve conter, pelo menos, (a) identificação dos integrantes do grupo, (b) breve descrição do trabalho feito, (c) apresentação das estruturas de dados utilizadas e justificativas necessárias e (d) uma seção detalhando como compilar e rodar o programa, com telas de exemplo da execução do sistema. Deixe claro que compilador usou (que versão, se utilizou alguma biblioteca diferente, qual sistema operacional utilizou, etc.).
 <br>
 <br>

### 5. Especificações
Nesta seção, são apresentadas as especificações funcionais do programa que será 
desenvolvido. Lembre-se de que só deve escolher uma das seguintes opções de sistema para 
desenvolver. Qualquer que seja a opção selecionada, faça uma implementação dinâmica e 
encadeada. Para questões específicas que não estejam especificadas, use o bom senso e 
documente suas decisões no relatório a ser entregue. Caso necessite, contate os monitores ou 
o professor da disciplina para tirar eventuais dúvidas.
<br>
<br>

### OPÇÃO 2 – sistema de compra online
#### Desenvolva um sistema de compra online, no estilo de leilão, em que vários usuários dão lances nos produtos disponíveis sendo vendidos. O dono do lance maior em um determinado momento leva o prêmio. Quando houver mais de um lance com o mesmo valor, quem deu o lance primeiro leva o prêmio.

* Qualquer produto que se queira vender pode ser cadastrado no sistema.
* Em um determinado momento, vários produtos podem estar disponíveis para o leilão e o usuário pode decidir em qual produto dar o lance.
* Um usuário pode dar quantos lances desejar para cada produto. 
* Cada novo lance tem que ser igual ou maior do que o lance anterior para um determinado produto. Dessa forma, pode ocorrer de vários usuários darem o mesmo lance para um produto. Nesse caso, deve-se guardar em uma lista os usuários que deram o mesmo lance para o produto e, ao final do leilão, o usuário cujo lance chegou primeiro ficará com o produto em questão.
* Além disso, deve-se ser possível recuperar o histórico de lances (com o nome dos usuários que os fizeram). Quando o leilão é dado por encerrado, listam-se os usuários dos maiores lances para cada produto.

#### Desta forma, o sistema de leilão online deve ter pelo menos as seguintes funcionalidades:
* a) cadastrar produto, lendo-se e armazenando-se em ordem alfabética o nome do produto (e, eventualmente, alguma descrição)
* b) listar na tela todos os produtos sendo leiloados, em ordem alfabética, mostrando todos os lances dados (os mais novos primeiro) e os nomes dos usuários que deram os lances (quando houver mais de um usuário por lance, liste os usuários na ordem em que deram o lance)
* c) dar um lance por um produto, sendo que o usuário deve dar seu nome, o valor do lance que deseja dar (que deve ser igual ou maior do que último lance para o produto em questão; caso contrário, o lance não deve ser aceito) e o produto pelo qual está dando o lance
* d) para os usuários que deram lances que já foram ultrapassados, listar outros produtos para os quais podem dar lances
* e) encerrar leilão, que lista o(s) usuário(s) e o lance ganhador para cada produto, e depois reinicializa o sistema para que novos leilões possam ocorrer
  
### A seguir, exibe-se um exemplo simples de execução do sistema.
``` 
Caro usuário, suas opções são:
1) cadastrar um produto
2) listar produtos e lances
3) dar um lance
4) listar outros produtos para lances
5) encerrar leilão

O que deseja fazer?
Resposta: 1
Entre com o nome do produto: televisão
Produto cadastrado com sucesso!

O que deseja fazer?
Resposta: 1
Entre com o nome do produto: computador
Produto cadastrado com sucesso!

O que deseja fazer?
Resposta: 3
Entre com seu nome: maria
Entre com o valor do lance: R$ 100,00
Entre com o nome do produto: televisão
Lance dado com sucesso!

O que deseja fazer?
Resposta: 3
Entre com seu nome: pedro
Entre com o valor do lance: R$ 90,00
Entre com o nome do produto: televisão
Seu lance pela televisão não foi aceito. Você precisa dar um lance maior!

O que deseja fazer?
Resposta: 3
Entre com seu nome: joão
Entre com o valor do lance: R$ 100,00
Entre com o nome do produto: televisão
Lance dado com sucesso!

O que deseja fazer?
Resposta: 3
Entre com seu nome: joão
Entre com o valor do lance: R$ 100,00
Entre com o nome do produto: computador
Lance dado com sucesso!

O que deseja fazer?
Resposta: 3
Entre com seu nome: pedro
Entre com o valor do lance: R$ 105,00
Entre com o nome do produto: computador
Lance dado com sucesso!

O que deseja fazer?
Resposta: 2
computador
1 lance de R$105,00: pedro
1 lance de R$100,00: joão
televisão
2 lances de R$100,00: maria, joão
Listagem completa!

O que deseja fazer?
Resposta: 4
para pedro: não gostaria de dar um lance pela televisão?
para maria: não gostaria de dar um lance pelo computador?
Leilão encerrado!

O que deseja fazer?
Resposta: 5
computador: pedro comprou por R$105,00
televisão: maria comprou por R$100,00
Leilão encerrado!
```

#### Funcionalidades extras também podem ser implementadas (e podem incrementar a nota do grupo), mas não são obrigatórias. Por exemplo, considerem implementar a função de remover um produto do leilão.
#### Atenção: a implementação deste sistema envolve obrigatoriamente o uso de listas (lista ordenada de produtos), pilhas (de lances dados para cada produto) e filas (de usuários que deram cada lance, por produto), dentre outras que julgar necessárias
