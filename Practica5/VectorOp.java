class VectOp {

    // Suma de Vectores
    public static Vector3D suma(Vector3D a, Vector3D b) {
        return new Vector3D(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
    }

    // Resta de Vectores
    public static Vector3D resta(Vector3D a, Vector3D b) {
        return new Vector3D(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
    }

    // Producto Punto (retorna un escalar 'double')
    public static double productoPunto(Vector3D a, Vector3D b) {
        return (a.getX() * b.getX()) + (a.getY() * b.getY()) + (a.getZ() * b.getZ());
    }

    // Producto Cruz (retorna un nuevo Vector3D)
    public static Vector3D productoCruz(Vector3D a, Vector3D b) {
        double x = a.getY() * b.getZ() - a.getZ() * b.getY();
        double y = a.getZ() * b.getX() - a.getX() * b.getZ();
        double z = a.getX() * b.getY() - a.getY() * b.getX();
        return new Vector3D(x, y, z);
    }

    // Comparación de Vectores
    public static boolean comparar(Vector3D a, Vector3D b) {
        return a.getX() == b.getX() && a.getY() == b.getY() && a.getZ() == b.getZ();
    }
}
