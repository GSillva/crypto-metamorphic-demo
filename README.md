# Minimal Cryptographic Metamorphic Testing Demo

Este projeto é uma demonstração didática, mínima, da ideia de
**cryptographically-informed metamorphic testing** apresentada em:

> Giacomo Fenzi, Jan Gilcher, Fernando Virdia —
> *Finding Bugs and Features Using Cryptographically-Informed Functional Testing*

O projeto **não implementa um KEM criptograficamente seguro**. O KEM em
`src/kem.c` é propositalmente um brinquedo para deixar a ideia fácil de
apresentar.

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

No GitHub Actions, isso aparece como um workflow vermelho.

## Relação com o paper

O paper original do Virdia et al. generaliza a ideia de metamorphic testing
para KEMs e esquemas de assinatura digital. O framework do trabalho separa
a geração do input (`GenInput`), a execução (`Call`), a mutação (`Maul`) e
a comparação/verificação (`Match`).

Este projeto reduz essa arquitetura a um único caso:

```text
Decaps(sk, c)
      ↓
    Maul
      ↓
Decaps(sk, c')
      ↓
    Match
```

O próximo passo seria substituir o toy KEM por uma implementação real,
por exemplo através de liboqs, e então introduzir AFL++ para explorar
automaticamente diferentes mutações.
