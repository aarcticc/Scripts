
# Symbolic Differentiation Engine in C — Projekt-Blueprint (Variante C)

**Ziel:** Voll ausgestattetes, moduläres C-Projekt zur symbolischen Ableitung beliebiger Ausdrücke.  
**Variante:** C — maximale Variante mit Mehrvariablen-Unterstützung, erweiterbarer Funktions-Registry, AST-Visualisierung, numerischer Evaluierung und professionellem Simplifier.

---

## Inhaltsverzeichnis
1. Überblick & Scope  
2. Architektur-Übersicht (Module & Verantwortlichkeiten)  
3. Dateistruktur (Projekt-Layout)  
4. Detaillierte API-Spezifikation je Modul (Header/Functions ohne Implementierungscode)  
5. Datenstrukturen & Typdefinitionen  
6. Grammatik & Parsing-Strategie  
7. Differentiationsregeln (vollständige Spezifikation)  
8. Vereinfachungsstrategie & Regeln  
9. AST-Printer & Pretty-Printer-Richtlinien  
10. Numerische Evaluierung API  
11. Fehlerbehandlung & Logging  
12. Tests, Metriken & CI-Vorgaben  
13. Debugging & AST-Visualisierung (Graphviz)  
14. Build- und Release-Anleitung  
15. Erweiterungs-Roadmap & mögliche Features  
16. Appendix: Beispiel-Ausdrücke und erwartete Ableitungen

---

## 1. Überblick & Scope
Dieses Dokument beschreibt ein komplettes C-Projekt (Produktionstauglich) zur symbolischen Differentiation. Zielnutzer sind Entwickler, die eine native, portable C-Bibliothek bzw. CLI benötigen, die:

- Eingabe von Funktionen als String (z. B. `"3*x^2 + sin(y) - ln(x)"`)
- Parst Ausdrücke in AST
- Führt symbolische Ableitung durch (mehrere Variablen, partielle Ableitungen)
- Simplifiziert Ergebnis-AST
- Druckt Ergebnis als String oder gibt numerische Evaluierung zurück
- Exportiert AST als Graphviz DOT
- Ist modular, testbar und erweiterbar

Nicht im Scope: vollständige symbolische Integration, CAS-reiche Features (z. B. Gröbsteilsätze), formale Beweiserweiterungen.

---

## 2. Architektur-Übersicht (Module & Verantwortlichkeiten)

- `lexer` — Tokenizer: Zeichenstrom → Tokenliste
- `parser` — Recursive-descent Parser: Tokenliste → AST
- `ast` — AST-Knoten, Konstruktor/Destruktor, Helfer
- `derive` — Ableitungsengine: AST → abgeleiteter AST (inkl. partieller Ableitungen)
- `simplify` — Vereinfacher & Normalisierer
- `printer` — AST → String (Pretty-Printer)
- `eval` — Numerische Evaluierung eines AST (mit Variablenbindung)
- `functions` — Funktionsregistry: Definitionen, Arity, Metadaten
- `error` — Fehlercodes & Fehlerbehandlung
- `io` — CLI / Datei-Ein-/Ausgabe
- `debug` — Graphviz-export, AST-Dumps
- `tests` — Unit-Tests & Integrationstests

Jedes Modul hat ein `*.h` Header und ein `*.c` Implementationsfile.

---

## 3. Dateistruktur (Projekt-Layout)

```
symbolic-derivative-c/
├─ include/
│  ├─ token.h
│  ├─ parser.h
│  ├─ ast.h
│  ├─ derive.h
│  ├─ simplify.h
│  ├─ printer.h
│  ├─ eval.h
│  ├─ functions.h
│  ├─ error.h
│  └─ utils.h
├─ src/
│  ├─ lexer.c
│  ├─ parser.c
│  ├─ ast.c
│  ├─ derive.c
│  ├─ simplify.c
│  ├─ printer.c
│  ├─ eval.c
│  ├─ functions.c
│  ├─ io.c
│  └─ debug.c
├─ tests/
│  ├─ test_lexer.c
│  ├─ test_parser.c
│  ├─ test_derive.c
│  ├─ test_simplify.c
│  └─ test_eval.c
├─ examples/
│  ├─ example_cli.txt
│  └─ example_ast.dot
├─ tools/
│  └─ gen_function_table.py
├─ docs/
│  └─ design.md
├─ CMakeLists.txt
├─ Makefile
└─ README.md
```

---

## 4. Detaillierte API-Spezifikation je Modul

> **Hinweis**: Hier folgen *Signaturen* und semantische Beschreibungen — keine Implementierung.

### 4.1 token.h
- `typedef enum TokenType { TOK_NUM, TOK_IDENT, TOK_PLUS, TOK_MINUS, TOK_MUL, TOK_DIV, TOK_POW, TOK_LPAREN, TOK_RPAREN, TOK_COMMA, TOK_END, ... } TokenType;`
- `typedef struct Token { TokenType type; char *lexeme; double value; } Token;`
- `TokenList* tokenize(const char *input, ErrorContext *err);`

**Semantik:** `tokenize` erzeugt eine geordnete Liste von Tokens. `lexeme` ist null-terminated. Fehler werden in `err` gesetzt.

### 4.2 parser.h
- `typedef struct Parser Parser;`
- `Parser* parser_create(TokenList *tokens);`
- `ASTNode* parse_expression(Parser *p, ErrorContext *err);`
- `void parser_destroy(Parser *p);`

**Semantik:** `parse_expression` liefert eine AST-Wurzel oder setzt `err`.

### 4.3 ast.h
- `typedef enum NodeType { NODE_CONST, NODE_VAR, NODE_ADD, NODE_SUB, NODE_MUL, NODE_DIV, NODE_POW, NODE_NEG, NODE_FUNC } NodeType;`
- `typedef struct ASTNode { NodeType type; double value; char *name; struct ASTNode *left, *right; } ASTNode;`
- `ASTNode* ast_new_const(double v);`
- `ASTNode* ast_new_var(const char *name);`
- `ASTNode* ast_new_unary(NodeType type, ASTNode *child);`
- `ASTNode* ast_new_binary(NodeType type, ASTNode *left, ASTNode *right);`
- `void ast_free(ASTNode *n);`

**Semantik:** Speicherverwaltung klar regeln — jedweder `ast_new_*` gibt Heap-allokierten Knoten zurück. `ast_free` rekursiv.

### 4.4 functions.h
- `typedef struct FunctionDescriptor { const char *name; int arity; ASTNode* (*impl)(ASTNode **args, int argc); /* optional helper prototypes */ } FunctionDescriptor;`
- `void functions_register_builtin();`
- `const FunctionDescriptor* functions_lookup(const char *name);`
- `int functions_is_builtin(const char *name);`

**Semantik:** Registry enthält Metadaten (Arity, Differentiation-Strategie Hinweis).

### 4.5 derive.h
- `ASTNode* derive_node(ASTNode *n, const char *var, ErrorContext *err);`
- `ASTNode* derive_partial(ASTNode *n, const char *var);` (alias, no error)
- `void derive_register_custom_function(const char *name, ASTNode* (*deriv)(ASTNode *arg, const char *var));`

**Semantik:** `derive_node` returns a new AST representing derivative w.r.t `var`. Always allocate a new tree; original must remain unchanged.

### 4.6 simplify.h
- `ASTNode* simplify_ast(ASTNode *n);`
- `ASTNode* simplify_once(ASTNode *n);`
- `void simplify_register_rule(const char* name, ASTNode* (*rule)(ASTNode*));`

**Semantik:** `simplify_ast` applies rules exhaustively (or up to max-iterations) and returns a new tree (or the same pointer if in-place decisions are made). Must be deterministic.

### 4.7 printer.h
- `char* ast_to_string(ASTNode *n);` // caller frees
- `char* ast_to_pretty_string(ASTNode *n, int max_width);`

**Semantik:** Printer must honor precedence and add parentheses only when necessary. Pretty string may insert spaces and linebreaks.

### 4.8 eval.h
- `typedef struct VarBinding { const char *name; double value; } VarBinding;`
- `double eval_ast(ASTNode *n, VarBinding *bindings, size_t nb, ErrorContext *err);`

**Semantik:** `eval_ast` numerically evaluates node using bindings. Unknown variable sets `err`.

### 4.9 error.h
- `typedef struct ErrorContext { int code; char *message; } ErrorContext;`
- `void error_set(ErrorContext *e, int code, const char *fmt, ...);`
- `void error_clear(ErrorContext *e);`

---

## 5. Datenstrukturen & Typdefinitionen

- **TokenList**: dynamische Array-Struktur, Index-Zugriff, Länge.
- **ASTNode**: union-ähnliche Struktur: bei `NODE_CONST` ist `value` gesetzt; bei `NODE_VAR` `name` gesetzt; bei `NODE_FUNC` `name` und `left` gesetzt (or `left` array if arity >1).
- **Memory management**: konsistente `ast_alloc`, `ast_free`, und optional `ast_clone`.
- **String handling**: zentrale String-Utilities in `utils.h` (safe strdup, formatted allocation).

---

## 6. Grammatik & Parsing-Strategie

Verwende Recursive Descent mit folgende (erweiterte) Grammatik:

```
expression  → assignment
assignment  → IDENT "=" expression | logic
logic       → equality ( ("&&" | "||") equality )*
equality    → relational ( ("==" | "!=") relational )*
relational  → add ( ("<" | "<=" | ">" | ">=") add )*
add         → mul (("+" | "-") mul)*
mul         → unary (("*" | "/") unary)*
unary       → ("+"|"-") unary | power
power       → primary ("^" power)?
primary     → NUMBER | IDENT ( "(" args? ")" )? | "(" expression ")"
args        → expression ("," expression)*
```

**Erweiterungen:** Support für functions mit mehreren Argumenten (z. B. `pow(x,y)`) & assignment for convenience in REPL mode.

**Ambiguitäten:** Negative numbers are parsed as unary minus applied to constant number; distinguishes unary minus vs subtraction by grammar.

---

## 7. Differentiationsregeln (vollständige Spezifikation)

Allgemeine Vorgehensweise:
- `derive_node` erstellt einen neuen AST-Knoten, ruft rekursiv Ableitungen an und baut Formel gemäß Regel zusammen.

Regeln:

- `d/dx(c)` = `0`
- `d/dx(v)` = `1` wenn `v == var` sonst `0`
- `d/dx(f + g)` = `f' + g'`
- `d/dx(f - g)` = `f' - g'`
- `d/dx(f * g)` = `f' * g + f * g'`
- `d/dx(f / g)` = `(f' * g - f * g') / (g ^ 2)`
- `d/dx(u ^ n)` where n is constant = `n * u^(n-1) * u'`
- `d/dx(a ^ x)` where a constant = `a^x * ln(a) * x'` (if x is identity, x'=1)
- `d/dx(u ^ v)` (general) = `u^v * (v' * ln(u) + v * u' / u)`
- `d/dx(sin(u))` = `cos(u) * u'`
- `d/dx(cos(u))` = `-sin(u) * u'`
- `d/dx(tan(u))` = `sec(u)^2 * u'` or `(1 / cos(u)^2) * u'`
- `d/dx(exp(u))` = `exp(u) * u'`
- `d/dx(ln(u))` = `u' / u`
- `d/dx(sqrt(u))` = `u' / (2*sqrt(u))`
- `d/dx(atan2(y,x))` = formula for two-argument functions (explicit handling)
- **Chain Rule:** for `f(g(x))` → `f'(g(x)) * g'(x)` — apply for built-in functions via registry.

**Partielle Ableitung:** `derive_node` must accept variable name; for multi-variable AST, partial derivative w.r.t `x` treats other variables as constants.

**Custom Function Derivatives:** `functions.c` supports registration of derivative generators for user-defined functions. Signature: `ASTNode* derivative_of_fn(ASTNode *args[], int argc, const char *var)`.

---

## 8. Vereinfachungsstrategie & Regeln

Philosophie: Erzeuge zuerst korrekte Ableitung, dann vereinfache in mehreren Schritten:

**Phasen:**
1. **Local constant folding:** wenn beide Kinder Konstanten → ausrechnen
2. **Simple algebraic identities:** 0/1, multiplication by 0/1, addition with 0
3. **Flattening:** `(a + (b + c))` → `(a + b + c)` für Add und Mul (N-ary nodes)
4. **Power rules:** `x^1 → x`, `x^0 → 1` (with guard for `0^0` case)
5. **Negation normalization:** `-1 * x → -x` (unary NEG)
6. **Combine like terms:** optionally merge `2*x + 3*x → 5*x`
7. **Trigonometric simplifications:** `sin^2 + cos^2 → 1` (optional advanced rule)

**Iteration:** Apply rules iteratively until no change or max-iterations reached. Ensure idempotence in final pass.

**Performance note:** Heavy algebraic simplification (e.g., combining like terms, factorization) can be expensive — keep these behind separate flags (fast mode vs thorough mode).

---

## 9. AST-Printer & Pretty-Printer-Richtlinien

**Requirements:**
- Minimale Klammerung: nur wenn nötig aufgrund von Precedence/Associativity.
- For binary op nodes, use precedence table:
  - `^` highest, right-associative
  - `*` `/` next
  - `+` `-` lowest
- Unary minus must be printed tightly: `-x` or `-(a+b)` as needed.
- Functions: `sin(x)`, `pow(x,y)`
- Optional pretty options:
  - `compact` (no extra spaces)
  - `spaced` (spaces around operators)
  - `multiline` (wrap long expressions)
- `ast_to_string` returns malloc'd null-terminated string. Caller responsible to free.

---

## 10. Numerische Evaluierung API

- `double eval_ast(ASTNode *n, VarBinding *bindings, size_t nb, ErrorContext *err);`

**VarBinding lookup:** linear map or small hash-table. For performance, support compiled evaluation: `eval_compile_ast` that produces a bytecode-like VM or flattened RPN for fast repeated evaluations.

**Edge cases:** domain errors (sqrt negative, log non-positive) must set `err`.

---

## 11. Fehlerbehandlung & Logging

- `ErrorContext` zentral; returning pointers must check `err->code`.
- Log levels: `ERROR`, `WARN`, `INFO`, `DEBUG`
- `debug.c` can enable AST dumps only on debug level >= DEBUG.
- All public API functions return NULL or sentinel on error and set `ErrorContext`.

---

## 12. Tests, Metriken & CI-Vorgaben

**Unit tests:**
- Lexer tests: tokens for many cases incl. edge cases
- Parser tests: operator precedence, function calls, nested parentheses
- AST tests: construction & freeing
- Derive tests: known derivatives (see Appendix)
- Simplify tests: canonicalization
- Eval tests: numeric correctness vs reference values

**Integration tests:**
- Roundtrip: parse → derive → simplify → print → reparsable output
- Regression tests for tricky cases: `x^x`, `ln(x^2)`, `(sin(x))^2`

**CI:**
- Use CMake and `ctest` for unit tests
- GH Actions workflow: build, run tests, run sanitizers (ASAN/UBSAN)
- Code coverage: generate and enforce threshold (e.g., >= 80%)

---

## 13. Debugging & AST-Visualisierung (Graphviz)

**DOT Export:**
- `debug_export_dot(ASTNode *n, const char *filename);`
- Each node labeled with type and small string repr (truncated)
- Edges show `left`/`right`

**Usage:** After parse or derive, call export to inspect structure visually:
```
dot -Tpng example_ast.dot -o example_ast.png
```

**Additional:** Optional `ast_to_svg_inline` for embedding in docs.

---

## 14. Build- und Release-Anleitung

**Tooling:** CMake recommended; fallback Makefile provided.

**CMakeLists.txt essentials:**
- Project name + C standard (C11 or C17)
- Options: `-DENABLE_DEBUG=ON`, `-DENABLE_SLOW_SIMPLIFY=ON`
- Targets: `libsymbolic.a`, `cli`, `tests`

**Release packaging:**
- Create tarball with `include/` and `lib/` `bin/` and `LICENSE`
- Semantic versioning: MAJOR.MINOR.PATCH
- Changelog in `docs/CHANGELOG.md`

---

## 15. Erweiterungs-Roadmap & mögliche Features

- Symbolic simplification suite (factorization, expand, collect)
- Symbolic integration module (heuristic & table-based)
- Codegen: generate C, Python, or LLVM IR from AST
- JIT for numeric evaluation
- Multi-threaded evaluation for large expression sets
- Bindings: Python (CPython extension), Rust FFI, WebAssembly
- Expression caching & memoization
- Expression canonicalization & hashing for equality checks

---

## 16. Appendix: Beispiel-Ausdrücke und erwartete Ableitungen

1. `f(x) = 3*x^2 + 5*sqrt(x) - 1/x`  
   `f'(x) = 6*x + 5/(2*sqrt(x)) + 1/x^2`

2. `f(x,y) = x^2 * sin(y) + ln(x*y)`  
   `∂f/∂x = 2*x*sin(y) + 1/x`  
   `∂f/∂y = x^2*cos(y) + 1/y`

3. `f(x) = sin(x^2)`  
   `f'(x) = 2*x * cos(x^2)`

4. `f(x) = (x^x)`  
   `f'(x) = x^x * (ln(x) + 1)`

5. `f(x) = exp(2*x) * ln(x)`  
   `f'(x) = exp(2*x)*2*ln(x) + exp(2*x) * (1/x)`

---

## Schlussbemerkung (Praktische Hinweise)

- Beginne mit einem **umfangreichen Test-Set**; symbolische Systeme sind anfällig für Randfälle.  
- Implementiere `ast_clone` früh — Derive und Simplify arbeiten sicherer mit Kopien.  
- Halte API-Funktionen klein und explizit; favorisiere `const` wo möglich.  
- Dokumentiere alle Speicherallokationen & Ownership-Regeln in `docs/design.md`.  
- Nutze ASAN/UBSAN im CI, und einen Fuzzer (z. B. AFL/LibFuzz) gegen den Parser.
