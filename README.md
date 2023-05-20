Этот проект содержит в себе 5 классов:

1. Rational - позволяет совершать базовые арифметические действия с рациональными числами
2. VarInPower - вспомогательный класс для работы с переменной в степени
3. Monom - класс для базовых операций с одночленом
4. MonomWithCoef - вспомогательный класс для работы с одночленом с коэффициентом
5. Polynom - класс для работы с многочленами

Помимо этих 5 классов, в проекте содержится класс BaseAlgorithms, содержащий базовые алгоритмы теории базисов Гребнера:
1. ReduceOnPolynom - принимает 2 многочлена, возвращает результат полной редукции первого по второму
2. ReduceOnPolynomSet - принимает многочлен и вектор многочленов, возвращает результат редукции многочлена по множеству
3. BuhbergerAlgorithm - принимает вектор многочленов, возвращает этот же вектор, дополненный до базиса Гребнера алгоритмом Бухбергера
4. IsPolynomInIdeal - принимает многочлен и вектор многочленов, возвращает true, если многочлен принадлежит идеалу множества, false иначе
