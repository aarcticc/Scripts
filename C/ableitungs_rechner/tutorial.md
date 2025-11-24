# Tutorial: Building a Symbolic Differentiation Engine in C99  
## Zielgruppe  
Dieses Tutorial richtet sich an Entwickler mit ca. **1 Monat C99-Erfahrung**, die das Projekt aus `symbolic_derivative_project_C.md` vollständig umsetzen möchten. Es führt Schritt für Schritt vom Parsing über den AST bis hin zur Ableitung, Vereinfachung und Ausgabe.

---

# 1. Projektüberblick  
Du implementierst ein modular aufgebautes Symbolic-Math-Framework mit:

- **Tokenizer (Lexer)**
- **Parser → AST**
- **Ableitungsmodul**
- **Simplifier**
- **Pretty Printer**
- **Optional: Graphviz-Export**

Der Workflow läuft immer in diesem Muster:

```
Input-String → Lexer → Tokens → Parser → AST → Deriver → AST' → Simplifier → AST'' → Printer → Output
```

---

# 2. Code-Struktur (Empfohlen)
```
/src
  lexer.c
  parser.c
  ast.c
  derive.c
  simplify.c
  printer.c
  eval.c
  main.c
/include
  lexer.h
  parser.h
  ast.h
  derive.h
  simplify.h
  printer.h
  eval.h
```

---

# 3. Lexer Implementieren  
Der Lexer zerlegt einen Text wie:

```
3*x^2 + sin(x)
```

in Tokens wie:

```
NUMBER(3) MUL IDENT(x) POW NUMBER(2) PLUS IDENT(sin) LPAREN IDENT(x) RPAREN
```

### Schritte:

1. Zeichen lesen  
2. Whitespace ignorieren  
3. Zahlen erkennen (`isdigit`)  
4. Variablen und Funktionsnamen erkennen  
5. Operatoren erkennen (`+ - * / ^ ( )`)  
6. Token-Liste zurückgeben

### Beispielcode: Token-Struktur
```c
typedef enum {
    TOK_NUMBER,
    TOK_IDENT,
    TOK_PLUS, TOK_MINUS, TOK_MUL, TOK_DIV, TOK_POW,
    TOK_LPAREN, TOK_RPAREN,
    TOK_END,
    TOK_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char text[32];  
} Token;
```

---

# 4. Parser (Recursive Descent)  
Der Parser erzeugt aus Tokens einen **AST (Abstract Syntax Tree)**.

## Grammatik (empfohlen)
```
expr    → term (("+" | "-") term)*
term    → factor (("*" | "/") factor)*
factor  → unary ("^" unary)*
unary   → ("+" | "-") unary | primary
primary → NUMBER | IDENT "(" expr ")" | IDENT | "(" expr ")"
```

### Beispiel: AST-Knoten
```c
typedef enum {
    AST_NUM,
    AST_VAR,
    AST_ADD,
    AST_SUB,
    AST_MUL,
    AST_DIV,
    AST_POW,
    AST_FUNC // sin, cos, ln, sqrt, ...
} ASTType;

typedef struct AST {
    ASTType type;
    double number;
    char ident[32];
    struct AST* left;
    struct AST* right;
} AST;
```

---

# 5. Ableitungsmodul  
Du implementierst die klassischen Regeln der Analysis:

## Beispiele
### Produktregel
```
d/dx (u*v) = u' * v + u * v'
```

### Quotientenregel
```
d/dx (u/v) = (u' * v - u * v') / (v^2)
```

### Potenzregel
```
d/dx (x^n) = n * x^(n-1)
```

### Kettenregel für Funktionen
```
d/dx f(g(x)) = f'(g(x)) * g'(x)
```

### Beispiel: Ableitungscode
```c
AST* derive(AST* n) {
    switch(n->type) {
        case AST_NUM:
            return ast_num(0);

        case AST_VAR:
            return ast_num(1);

        case AST_ADD:
            return ast_add(derive(n->left), derive(n->right));

        case AST_MUL:
            return ast_add(
                ast_mul(derive(n->left), n->right),
                ast_mul(n->left, derive(n->right))
            );

        case AST_POW:
            if (n->left->type == AST_VAR && n->right->type == AST_NUM) {
                double e = n->right->number;
                return ast_mul(ast_num(e),
                    ast_pow(ast_var("x"), ast_num(e - 1)));
            }
            return ast_mul(
                n,
                ast_add(
                    ast_mul(derive(n->right), ast_ln(n->left)),
                    ast_mul(n->right, ast_div(derive(n->left), n->left))
                )
            );

        case AST_FUNC:
            if (strcmp(n->ident, "sin") == 0)
                return ast_mul(ast_func("cos", n->left), derive(n->left));
            if (strcmp(n->ident, "cos") == 0)
                return ast_mul(ast_num(-1),
                               ast_mul(ast_func("sin", n->left), derive(n->left)));
            if (strcmp(n->ident, "ln") == 0)
                return ast_div(derive(n->left), n->left);

            return ast_mul(ast_func(n->ident, n->left), derive(n->left));
    }
    return NULL;
}
```

---

# 6. Vereinfachung (Simplifier)  
Beispiele:

- `x + 0 → x`
- `x * 1 → x`
- `x * 0 → 0`
- `0 / x → 0`
- `x^1 → x`
- `x^0 → 1`

### Beispielcode-Snippet
```c
if (n->type == AST_MUL) {
    if (is_num(n->left, 0) || is_num(n->right, 0))
        return ast_num(0);
    if (is_num(n->left, 1))
        return n->right;
    if (is_num(n->right, 1))
        return n->left;
}
```

---

# 7. Pretty Printer  
Wandelt den AST in mathematischen Text um.

```c
void print_ast(AST* n) {
    switch (n->type) {
        case AST_NUM: printf("%g", n->number); break;
        case AST_VAR: printf("%s", n->ident); break;
        case AST_ADD: 
            print_ast(n->left); printf(" + "); print_ast(n->right); 
            break;
        // ...
    }
}
```

---

# 8. Graphviz-Ausgabe (optional)
```
digraph {
  n1[label="*"];
  n2[label="x"];
  n3[label="3"];
  n1->n2;
  n1->n3;
}
```

---

# 9. main.c  
```c
int main() {
    char input[256];
    printf("Enter function: ");
    fgets(input, sizeof(input), stdin);

    TokenList tl = lex(input);
    AST* root = parse(&tl);

    AST* d = derive(root);
    AST* s = simplify(d);

    print_ast(s);
}
```

---

# 10. Abschluss  
Damit kannst du **jede beliebige mathematische Funktion parsen und automatisch ableiten**.
