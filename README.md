# Semáforo Sonoro para Deficientes Visuais

## Descrição
Este projeto consiste em um sistema de controle de sinais de trânsito para um cruzamento, projetado para auxiliar deficientes visuais na travessia segura de faixas de pedestres. O sistema utiliza um botão de acionamento para deficientes visuais que desencadeia uma sequência de fechamento do sinal de trânsito para veículos e ativa um sinal sonoro indicando permissão para a travessia.

## Objetivos
- Implementar um semáforo para pedestres com sinalização sonora.
- Criar um sistema interativo utilizando um botão de acionamento.
- Utilizar um Raspberry Pi Pico W para controle lógico do sistema.
- Simular e testar o sistema na plataforma Wokwi.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico W
- **LEDs:**
  - Verde, amarelo e vermelho para representar o semáforo dos carros.
  - Um LED verde para pedestres.
- **Buzzer:** Para emitir um som quando o pedestre pode atravessar.
- **Push Button:** Para simular a botoeira do pedestre.
- **Resistores:** Para LEDs e botão.
- **Protoboard e fiação** para conexões.

## Linguagem de Programação
Todo o projeto foi desenvolvido em **C** e estruturado para melhor organização e legibilidade do código.

## Funcionamento do Sistema
1. **Estado Inicial:** O semáforo dos carros alterna automaticamente entre verde (8s), amarelo (2s) e vermelho (10s). O LED verde para pedestres e o buzzer estão inativos.
2. **Ao pressionar o botão:**
   - O LED amarelo acende por 5s e o vermelho por 15s.
   - O LED verde para pedestres acende durante os 15s.
   - O buzzer emite um som intermitente indicando a permissão para atravessar.
3. **Pós-Travessia:** O sistema retorna à operação normal.

## Instalação e Execução
### **1. Configuração do Ambiente**
- Instale o **Raspberry Pi Pico SDK**.
- Utilize o **Wokwi** para simular o funcionamento.
- Certifique-se de que sua IDE (VS Code ou outra) tem suporte para C/C++ e para o Pico W.

### **2. Clonar o Repositório**
```sh
 git clone https://github.com/seu_usuario/semaforo_para_deficientes_visuais.git
 cd semaforo_para_deficientes_visuais
```

### **3. Compilar o Código**
Se estiver utilizando o SDK do Raspberry Pi Pico:
```sh
mkdir build
cd build
cmake ..
make
```

### **4. Upload para o Raspberry Pi Pico**
Após compilar, conecte o Raspberry Pi Pico ao PC e copie o arquivo `.uf2` gerado para a unidade correspondente.

### **5. Simulação pronta no Wokwi**
- Acesse [Wokwi](https://wokwi.com/projects/417824797195482113).

## Autor
Lucas Pereira Castanheira Nascimento

## Licença
Este projeto está sob a licença MIT. Consulte o arquivo `LICENSE` para mais detalhes.


