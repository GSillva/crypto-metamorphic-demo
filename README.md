# Minimal Cryptographic Metamorphic Testing Demo

Este projeto é uma demonstração mínima da ideia de
**cryptographically-informed metamorphic testing** apresentada em:

> Giacomo Fenzi, Jan Gilcher, Fernando Virdia —
> *Finding Bugs and Features Using Cryptographically-Informed Functional Testing*

O projeto **não implementa um KEM criptograficamente seguro**. 
## Ideia

O teste segue uma versão reduzida do fluxo:

```text
GenInput → Call → Maul → Call → Match
```

1. `GenInput`: gera `(pk, sk)` e um ciphertext válido `c`.
2. `Call`: verifica que `c` é aceito por `Decaps(sk, c)`.
3. `Maul`: altera um único bit de `c`, produzindo `c'`.
4. `Call`: executa `Decaps(sk, c')`.
5. `Match`: verifica a propriedade definida para este exemplo:
   um ciphertext alterado deve ser rejeitado.

Se a implementação aceitar `c'`, o teste retorna código de saída `1`.
Isso faz o GitHub Actions marcar o workflow como falho.

## GitHub Actions

O workflow está em:

```text
.github/workflows/crypto-test.yml
```

Ele roda em `push` e `pull_request`, compila com `make` e executa
`make test`.

## Como demonstrar

Localmente:

```bash
make
make test
```

Resultado esperado:

```text
PASS: modified ciphertext was rejected
```

Para demonstrar uma falha, altere temporariamente `kem_decaps()` para
aceitar sempre o ciphertext:

```c
return 1;
```

Depois:

```bash
make test
```

O teste deve produzir:

```text
METAMORPHIC VIOLATION: modified ciphertext was accepted
```

e terminar com código `1`.


