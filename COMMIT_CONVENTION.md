# Commit Convention

We use **Conventional Commits**. Every commit must follow this format:

```
<type>[(scope)]: <short description>
```

## Types

| Type | Use it for |
|---|---|
| `feat` | new class, method, or feature |
| `fix` | bug correction |
| `refactor` | restructuring without behavior change |
| `chore` | build system, CMake, tooling |
| `docs` | README, comments, scene files |
| `style` | formatting or naming only |
| `test` | tests |

## Scopes (optional)

`math` · `core` · `primitives` · `lights` · `parser` · `factory` · `renderer`

## Rules

- Lowercase, no period at the end, ≤ 72 chars total.
- Breaking change: add `!` → `refactor!(primitives): rename hits signature`

## Examples

```
feat(math): add Vector3D with length and dot
feat(primitives): sphere ray intersection
fix(renderer): off-by-one in ppm row loop
refactor(primitives): sphere derives from APrimitive
chore: register math sources in CMakeLists
```
