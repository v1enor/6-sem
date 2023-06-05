import sklearn
import mglearn
import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import warnings
warnings.filterwarnings("ignore")

mglearn.plots.plot_linear_regression_wave()
plt.show()

from sklearn.linear_model import LinearRegression
X, y = mglearn.datasets.make_wave(n_samples=60)
from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=42)

lr = LinearRegression().fit(X_train, y_train)

print("lr.coef_: {}".format(lr.coef_))
print("lr.intercept_: {}".format(lr.intercept_))

print("Правильность на обучающемнаборе: {:.2f}".format(lr.score(X_train, y_train)))
print("Правильность на тестовомнаборе: {:.2f}".format(lr.score(X_test, y_test)))

X, y = mglearn.datasets.load_extended_boston()
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=0)
lr = LinearRegression().fit(X_train, y_train)

print("Правильность на обучающемнаборе: {:.2f}".format(lr.score(X_train, y_train)))
print("Правильность на тестовомнаборе: {:.2f}".format(lr.score(X_test, y_test)))

print("---------------Гребневая---------------")
from sklearn.linear_model import Ridge
ridge = Ridge().fit(X_train, y_train)
print("Правильность на обучающемнаборе: {:.2f}".format(ridge.score(X_train, y_train)))
print("Правильность на тестовомнаборе: {:.2f}".format(ridge.score(X_test, y_test)))

print("alpha=10")
ridge10 = Ridge(alpha=10).fit(X_train, y_train)
print("Правильность на обучающемнаборе: {:.2f}".format(ridge10.score(X_train, y_train)))
print("Правильность на тестовомнаборе: {:.2f}".format(ridge10.score(X_test, y_test)))

print("alpha=0.1")
ridge01 = Ridge(alpha=0.1).fit(X_train, y_train)
print("Правильность на обучающемнаборе: {:.2f}".format(ridge01.score(X_train, y_train)))
print("Правильность на тестовомнаборе: {:.2f}".format(ridge01.score(X_test, y_test)))

plt.plot(ridge.coef_, 's', label="Гребневаярегрессия alpha=1")
plt.plot(ridge10.coef_, '^', label="Гребневаярегрессия alpha=10")
plt.plot(ridge01.coef_, 'v', label="Гребневаярегрессия alpha=0.1")

plt.plot(lr.coef_, 'o', label="Линейнаярегрессия")
plt.xlabel("Индекскоэффициента")
plt.ylabel("Оценкакоэффициента")
plt.hlines(0, 0, len(lr.coef_))
plt.ylim(-25, 25)
plt.legend()
plt.show()

mglearn.plots.plot_ridge_n_samples()
plt.show()

print("---------------Лассо---------------")
from sklearn.linear_model import Lasso
lasso = Lasso().fit(X_train, y_train)
print("Правильность на обучающемнаборе: {:.2f}".format(lasso.score(X_train, y_train)))
print("Правильность на контрольномнаборе: {:.2f}".format(lasso.score(X_test, y_test)))
print("Количество использованных признаков: {}".format(np.sum(lasso.coef_ != 0)))

print("alpha=0.01")
lasso001 = Lasso(alpha=0.01, max_iter=100000).fit(X_train, y_train)
print("Правильность на обучающемнаборе: {:.2f}".format(lasso001.score(X_train, y_train)))
print("Правильностьнатестовомнаборе: {:.2f}".format(lasso001.score(X_test, y_test)))
print("Количество использованных признаков: {}".format(np.sum(lasso001.coef_ != 0)))

print("alpha=0.0001")
lasso00001 = Lasso(alpha=0.0001, max_iter=100000).fit(X_train, y_train)
print("Правильность на обучающемнаборе: {:.2f}".format(lasso00001.score(X_train, y_train)))
print("Правильностьнатестовомнаборе: {:.2f}".format(lasso00001.score(X_test, y_test)))
print("Количество использованных признаков: {}".format(np.sum(lasso00001.coef_ != 0)))

plt.plot(lasso.coef_, 's', label="Лассо alpha=1")
plt.plot(lasso001.coef_, '^', label="Лассо alpha=0.01")
plt.plot(lasso00001.coef_, 'v', label="Лассо alpha=0.0001")

plt.plot(ridge01.coef_, 'o', label="Гребневаярегрессия alpha=0.1")
plt.legend(ncol=2, loc=(0, 1.05))
plt.ylim(-25, 25)
plt.xlabel("Индекскоэффициента")
plt.ylabel("Оценкакоэффициента")
plt.show()