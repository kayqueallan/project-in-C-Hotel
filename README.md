# Descanso Garantido - Sistema de Gestão de Hotel

Este projeto em C foi desenvolvido por Kayque Allan e Felipe Augusto como parte do trabalho interdisciplinar entre Fundamentos de Engenharia de Software e Algoritmos e Estruturas de Dados I.

## Introdução

O Descanso Garantido é um hotel localizado no centro de Itacaré – BA, que visa oferecer um serviço de qualidade aos seus clientes, buscando também a fidelização dos mesmos. Até o momento, o hotel vinha enfrentando dificuldades de organização devido ao uso de planilhas do Excel e cadernos para o controle de estadias, clientes e funcionários. Problemas como reserva duplicada de quartos e falta de integração entre informações foram identificados.

Diante desses desafios, o hotel contratou uma empresa desenvolvedora para criar um software específico que permita gerenciar de forma eficiente as operações diárias.

## Funcionalidades do Sistema

1. **Cadastro de Cliente**: Permite registrar clientes com informações como código, nome, endereço e telefone. Garante que não haja clientes duplicados.

2. **Cadastro de Funcionário**: Permite registrar funcionários com informações como código, nome, telefone, cargo e salário. Também garante que não haja funcionários duplicados.

3. **Cadastro de Estadia**: Registra uma estadia, associando-a a um cliente e a um quarto disponível. Verifica a disponibilidade do quarto e calcula automaticamente a quantidade de diárias com base nas datas de entrada e saída.

4. **Baixa de Estadia**: Finaliza uma estadia, calculando o valor total a ser pago pelo cliente e marcando o quarto como desocupado.

5. **Pesquisa de Cliente e Funcionário**: Permite buscar informações detalhadas de clientes e funcionários pelo nome ou código.

6. **Consulta de Estadias por Cliente**: Mostra na tela todas as estadias de um determinado cliente.

## Restrições e Observações

- Para cadastrar uma estadia, o cliente e o quarto devem estar previamente cadastrados.
- Estadias só podem ser cadastradas para quartos com status "desocupado".
- Não é permitido mais de uma estadia para o mesmo quarto no mesmo período.
- O sistema deve persistir todas as informações em arquivos para garantir a integridade dos dados.

## Implementação e Execução

O projeto foi desenvolvido em C, utilizando conceitos de Estruturas de Dados e boas práticas de Engenharia de Software. Cada funcionalidade foi implementada como uma função específica, garantindo modularidade e facilitando a manutenção do código.

### Como Executar

1. Clone o repositório para sua máquina local.
2. Compile o código-fonte utilizando um compilador C compatível.
3. Execute o programa principal (`main.c`).

## Conclusão

Este projeto não apenas atende às necessidades do Hotel Descanso Garantido, mas também demonstra a aplicação prática dos conceitos aprendidos em sala de aula nas disciplinas de Engenharia de Software e Algoritmos e Estruturas de Dados I. A utilização de metodologias ágeis como Scrum para o gerenciamento do desenvolvimento foi fundamental para o sucesso do projeto.

Para mais detalhes, consulte o código-fonte e a documentação fornecida.
