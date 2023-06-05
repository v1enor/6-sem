import os
import warnings

import mglearn
import numpy as np
import matplotlib.pyplot as plt

from IPython.display import display
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.datasets import make_moons
from sklearn.datasets import load_breast_cancer


def plot_single_hidden_layer_graph_show():
    display(mglearn.plots.plot_single_hidden_layer_graph())

    line = np.linspace(-3, 3, 100)
    plt.plot(line, np.tanh(line), label='tanh')
    plt.plot(line, np.maximum(line, 0), label='relu')
    plt.legend(loc='best')
    plt.xlabel('x')
    plt.ylabel('relu(x), tanh(x)')
    plt.show()

    mglearn.plots.plot_single_hidden_layer_graph()
    plt.show()


def MLPClassifier_show():
    X, y = make_moons(n_samples=100, noise=0.25, random_state=3)
    X_train, X_test, y_train, y_test = train_test_split(X, y, stratify=y, random_state=3)

    mlp = MLPClassifier(solver='lbfgs', random_state=0).fit(X_train, y_train)
    mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3)
    mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train)
    plt.xlabel('Признак 0')
    plt.ylabel('Признак 1')
    plt.show()

    mlp = MLPClassifier(solver='lbfgs', random_state=0, hidden_layer_sizes=[10]).fit(X_train, y_train)
    mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3)
    mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train)
    plt.xlabel('Признак 0')
    plt.ylabel('Признак 1')
    plt.show()

    mlp = MLPClassifier(solver='lbfgs', random_state=0, hidden_layer_sizes=[10, 10]).fit(X_train, y_train)
    mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3)
    mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train)
    plt.xlabel('Признак 0')
    plt.ylabel('Признак 1')
    plt.show()

    mlp = MLPClassifier(solver='lbfgs', activation='tanh', random_state=0,
                        hidden_layer_sizes=[10, 10]).fit(X_train, y_train)
    mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3)
    mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train)
    plt.xlabel('Признак 0')
    plt.ylabel('Признак 1')
    plt.show()

    fig, axes = plt.subplots(2, 4, figsize=(20, 8))
    for axx, n_hidden_nodes in zip(axes, [10, 100]):
        for ax, alpha in zip(axx, [0.0001, 0.01, 0.1, 1]):
            mlp = MLPClassifier(solver='lbfgs', random_state=0, hidden_layer_sizes=[n_hidden_nodes, n_hidden_nodes],
                                alpha=alpha).fit(X_train, y_train)
            mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3, ax=ax)
            mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train, ax=ax)
            ax.set_title(f'n_hidden=[{n_hidden_nodes}, {n_hidden_nodes}]\n alpha={alpha}')
    plt.show()

    fig, axes = plt.subplots(2, 4, figsize=(20, 8))
    for i, ax in enumerate(axes.ravel()):
        mlp = MLPClassifier(solver='lbfgs', random_state=i,
                            hidden_layer_sizes=[100, 100], alpha=alpha).fit(X_train, y_train)
        mglearn.plots.plot_2d_separator(mlp, X_train, fill=True, alpha=0.3, ax=ax)
        mglearn.discrete_scatter(X_train[:, 0], X_train[:, 1], y_train, ax=ax)
    plt.show()


def cancer_show():
    cancer = load_breast_cancer()
    X_train, X_test, y_train, y_test = train_test_split(cancer.data, cancer.target, random_state=0)
    mlp = MLPClassifier(random_state=42).fit(X_train, y_train)

    print(f'Правильность на обучающем наборе: {mlp.score(X_train, y_train)}\n'
          f'Правильность на тестовом наборе: {mlp.score(X_test, y_test)}\n')

    min_on_training = X_train.min(axis=0)
    range_on_training = (X_train - min_on_training).max(axis=0)
    X_train_scaled = (X_train - min_on_training) / range_on_training
    mean_on_train = X_train.mean(axis=0)
    std_on_train = X_train.std(axis=0)
    X_test_scaled = (X_test - mean_on_train) / std_on_train

    mlp = MLPClassifier(random_state=0).fit(X_train_scaled, y_train)
    print(f'Правильность на обучающем наборе: {mlp.score(X_train_scaled, y_train)}\n'
          f'Правильность на тестовом наборе: {mlp.score(X_test_scaled, y_test)}\n')

    mlp = MLPClassifier(max_iter=1000, random_state=0).fit(X_train_scaled, y_train)
    print(f'Правильность на обучающем наборе: {mlp.score(X_train_scaled, y_train)}\n'
          f'Правильность на тестовом наборе: {mlp.score(X_test_scaled, y_test)}\n')

    mlp = MLPClassifier(max_iter=1000, alpha=1, random_state=0).fit(X_train_scaled, y_train)
    print(f'Правильность на обучающем наборе: {mlp.score(X_train_scaled, y_train)}\n'
          f'Правильность на тестовом наборе: {mlp.score(X_test_scaled, y_test)}\n')

    plt.figure(figsize=(20, 5))
    plt.imshow(mlp.coefs_[0], interpolation='none', cmap='viridis')
    plt.yticks(range(30), cancer.feature_names)
    plt.xlabel('Столбцы матрицы весов')
    plt.ylabel('Входная характеристика')
    plt.colorbar()
    plt.show()


def main():
    os.environ["PATH"] += os.pathsep + 'C:\Program Files\Graphviz\\bin\\'  # Изменить под свой путь
    warnings.filterwarnings('ignore')

    plot_single_hidden_layer_graph_show()
    MLPClassifier_show()
    cancer_show()
    pass


main()
