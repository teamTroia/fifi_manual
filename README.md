## Fifi manual

### Instalação

1. Clone esse repositório numa pasta de escolha
   
```bash
git clone git@github.com:teamTroia/fifi_manual.git
```

2. Crie um diretório e entre nele

```bash
mkdir build && cd build
```

3. Rode o cmake

```bash
cmake ..
```

4. Compile o código

```bash
make
```
5. Por fim, rode o executável

```bash
cd ..
./fifiSoccerTeam
```

### Rodando o projeto

1. Para realizar a comunicação com os robôs, é necessário colocar a porta em que o USB com a comunicação está conectado. Então deve-se descobrir qual o nome da porta que está conectado

```bash
dmesg | grep tty
```

2. Após determinar a porta, digite no primeiro campo da interface, por exemplo

```bash
/dev/ttyUSB0
```

3. Por fim, coloque o ID correspondente ao robô que deseja controlar e aperte em iniciar, note que no terminal será impresso uma mensagem "im a server". Em seguida, controle o robô com W, A, S e D.
