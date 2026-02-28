void printMatrix(GaussJordanResult gj) {
    for (int i = 0; i < gj.size; i++) {
        printf("|\t");
        for (int j = 0; j < gj.size; j++) {
            printf("%0.2f\t", gj.matrix[i][j]);
            
        }
        printf("| %0.2f\n", gj.vector[i]);
    }
    printf("\n");
}
