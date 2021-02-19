# similated life
## Что это?
Есть среда n * m блоков. В каждом блоке может находится агент или еда.

Агенты получают информацию о наличии в ближайших блоках еды и других агентов. Каждый агент принимает решение о действии: певернуть, пойти прямо, съесть еду и т.д. В качестве способа принятия решения используется нейронная сеть с выходным нейроном на каждое действие, применятся действие, выход на котором больше.

На каждое действие агента тратится энергия, когда она заканчивается начинает тратиться здоровье и в итоге агенты умирают. После смерти все агентов генерируется новое поколение, в котором часть польностью новые агенты полученные рандомно, а часть агенты из прошлого поколения, возможно с небольшими мутациями. Чем дольше жил агент, тем больше его шанс на наличие его "потомка" в следующем поколении.

В первых поколениях агенты либо стоят на месте, либо всё время идут прямо, игнорируя еду. Через какое-то число поколений паттерны поведения становятся более сложными и дают им возможность жить пока на карте есть еда.

## Управление
Пока есть только возможно пропустить 100'000 итераций, нажав пробел. Надеюсь в дальнейшем появится более удобное управление.

## Как это компилировать?
Прописать в CMakeLists.txt правильный путь к SFML. В CLion с MinGW прекрасно компилируется.