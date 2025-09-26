## Estrutura do Jogo

nome_do_jogo/
├── assets/                # Texturas, fontes, sons
│   └── player.bmp
├── build/                 # Compilados
├── src/
│   ├── main.c
│   ├── engine/
│   │   ├── render.c/.h
│   │   ├── input.c/.h
│   ├── game/
│   │   ├── player.c/.h
│   └── core/
│       └── game.c/.h
├── include/               # Headers compartilhados
├── CMakeLists.txt
└── README.md