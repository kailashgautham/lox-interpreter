// #include <string>
//
// class AstPrinter {
// public:
//     std::string print(Expr expr) {
//         return expr.accept(this);
//     }
//
//
//     std::string visitBinaryExpr(Expr.Binary expr) {
//         return parenthesize(expr.operator.lexeme,
//                             expr.left, expr.right);
//     }
//
//
//     std::string visitGroupingExpr(Expr.Grouping expr) {
//         return parenthesize("group", expr.expression);
//     }
//
//
//     std::string visitLiteralExpr(Expr.Literal expr) {
//         if (expr.value == null) return "nil";
//         return expr.value.toString();
//     }
//
//
//     std::string visitUnaryExpr(Expr.Unary expr) {
//         return parenthesize(expr.operator.lexeme, expr.right);
//     }
//
// private:
//     std::string parenthesize(std::string name, Expr... exprs) {
//         StringBuilder builder = new StringBuilder();
//
//         builder.append("(").append(name);
//         for (Expr expr: exprs) {
//             builder.append(" ");
//             builder.append(expr.accept(this));
//         }
//         builder.append(")");
//
//         return builder.toString();
//     }
// };
