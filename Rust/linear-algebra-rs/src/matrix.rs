use crate::linnum::LinNum;
use std::ops::{Add, AddAssign, Div, DivAssign, Index, IndexMut, Mul, MulAssign, Sub, SubAssign};

#[macro_export]
macro_rules! matrix {
    ($([$($value:expr),*]),*) => {
        LinMatrix::from(&[
            $(&[ $(lnum!($value)),* ]),*
        ])
    };
}

#[derive(Debug, PartialEq, Clone)]
pub enum MatrixError {
    DimensionMismatch,
}

#[derive(Debug, PartialEq, Clone)]
pub struct LinMatrix {
    rows: usize,
    cols: usize,
    data: Vec<LinNum>,
}

impl LinMatrix {
    pub fn new(rows: usize, cols: usize) -> LinMatrix {
        LinMatrix {
            rows,
            cols,
            data: vec![LinNum::new_real(0.0); rows * cols],
        }
    }

    pub fn from(data: &[&[LinNum]]) -> LinMatrix {
        let rows = data.len();
        let cols = data[0].len();
        let mut matrix = LinMatrix::new(rows, cols);
        for (i, row) in data.iter().enumerate() {
            for (j, &value) in row.iter().enumerate() {
                matrix.set(i, j, value);
            }
        }
        matrix
    }

    pub fn dim(&self) -> (usize, usize) {
        (self.rows, self.cols)
    }

    pub fn get(&self, row: usize, col: usize) -> LinNum {
        self.data[row * self.cols + col]
    }

    pub fn set(&mut self, row: usize, col: usize, value: LinNum) {
        self.data[row * self.cols + col] = value;
    }

    pub fn transpose(&self) -> LinMatrix {
        let mut result = LinMatrix::new(self.cols, self.rows);
        for i in 0..self.rows {
            for j in 0..self.cols {
                result.set(j, i, self.get(i, j));
            }
        }
        result
    }
}

impl Index<(usize, usize)> for LinMatrix {
    type Output = LinNum;

    fn index(&self, index: (usize, usize)) -> &Self::Output {
        &self.data[index.0 * self.cols + index.1]
    }
}

impl IndexMut<(usize, usize)> for LinMatrix {
    fn index_mut(&mut self, index: (usize, usize)) -> &mut Self::Output {
        &mut self.data[index.0 * self.cols + index.1]
    }
}

impl Add for LinMatrix {
    type Output = LinMatrix;

    fn add(self, other: LinMatrix) -> LinMatrix {
        let mut result = LinMatrix::new(self.rows, self.cols);
        for i in 0..self.rows {
            for j in 0..self.cols {
                result.set(i, j, self.get(i, j) + other.get(i, j));
            }
        }
        result
    }
}

impl AddAssign for LinMatrix {
    fn add_assign(&mut self, other: LinMatrix) {
        for i in 0..self.rows {
            for j in 0..self.cols {
                self.set(i, j, self.get(i, j) + other.get(i, j));
            }
        }
    }
}

impl Sub for LinMatrix {
    type Output = LinMatrix;

    fn sub(self, other: LinMatrix) -> LinMatrix {
        let mut result = LinMatrix::new(self.rows, self.cols);
        for i in 0..self.rows {
            for j in 0..self.cols {
                result.set(i, j, self.get(i, j) - other.get(i, j));
            }
        }
        result
    }
}

impl SubAssign for LinMatrix {
    fn sub_assign(&mut self, other: LinMatrix) {
        for i in 0..self.rows {
            for j in 0..self.cols {
                self.set(i, j, self.get(i, j) - other.get(i, j));
            }
        }
    }
}

impl Mul<LinNum> for LinMatrix {
    type Output = LinMatrix;

    fn mul(self, other: LinNum) -> LinMatrix {
        let mut result = LinMatrix::new(self.rows, self.cols);
        for i in 0..self.rows {
            for j in 0..self.cols {
                result.set(i, j, self.get(i, j) * other);
            }
        }
        result
    }
}

impl MulAssign<LinNum> for LinMatrix {
    fn mul_assign(&mut self, other: LinNum) {
        for i in 0..self.rows {
            for j in 0..self.cols {
                self.set(i, j, self.get(i, j) * other);
            }
        }
    }
}

impl Div<LinNum> for LinMatrix {
    type Output = LinMatrix;

    fn div(self, other: LinNum) -> LinMatrix {
        let mut result = LinMatrix::new(self.rows, self.cols);
        for i in 0..self.rows {
            for j in 0..self.cols {
                result.set(i, j, self.get(i, j) / other);
            }
        }
        result
    }
}

impl DivAssign<LinNum> for LinMatrix {
    fn div_assign(&mut self, other: LinNum) {
        for i in 0..self.rows {
            for j in 0..self.cols {
                self.set(i, j, self.get(i, j) / other);
            }
        }
    }
}

impl Mul<LinMatrix> for LinMatrix {
    type Output = Result<LinMatrix, MatrixError>;
    fn mul(self, other: LinMatrix) -> Result<LinMatrix, MatrixError> {
        if self.cols != other.rows {
            return Err(MatrixError::DimensionMismatch);
        }
        let mut result = LinMatrix::new(self.rows, other.cols);
        for i in 0..self.rows {
            for j in 0..other.cols {
                let mut sum = LinNum::new_real(0.0);
                for k in 0..self.cols {
                    sum += self.get(i, k) * other.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        Ok(result)
    }
}

impl std::fmt::Display for LinMatrix {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        for i in 0..self.rows {
            write!(f, "[ ")?;
            for j in 0..self.cols {
                write!(f, "{} ", self.get(i, j))?;
            }
            writeln!(f, "]")?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn it_works() {
        let matrix = matrix!([1.0, 2.0, 3.0], [4.0, 5.0, 6.0]);
        assert_eq!(matrix.dim(), (2, 3));
        assert_eq!(matrix.get(0, 0), lnum!(1.0));
        assert_eq!(matrix.get(1, 2), lnum!(6.0));
        assert_eq!(
            matrix.transpose(),
            matrix!([1.0, 4.0], [2.0, 5.0], [3.0, 6.0])
        );
    }

    #[test]
    fn test_add() {
        let matrix1 = matrix!([1.0, 2.0], [3.0, 4.0]);
        let matrix2 = matrix!([5.0, 6.0], [7.0, 8.0]);
        let result = matrix1 + matrix2;
        assert_eq!(result, matrix!([6.0, 8.0], [10.0, 12.0]));
    }

    #[test]
    fn test_sub() {
        let matrix1 = matrix!([1.0, 2.0], [3.0, 4.0]);
        let matrix2 = matrix!([5.0, 6.0], [7.0, 8.0]);
        let result = matrix1 - matrix2;
        assert_eq!(result, matrix!([-4.0, -4.0], [-4.0, -4.0]));
    }

    #[test]
    fn test_mul() {
        let matrix = matrix!([1.0, 2.0], [3.0, 4.0]);
        let result = matrix * lnum!(2.0);
        assert_eq!(result, matrix!([2.0, 4.0], [6.0, 8.0]));
    }

    #[test]
    fn test_div() {
        let matrix = matrix!([2.0, 4.0], [6.0, 8.0]);
        let result = matrix / lnum!(2.0);
        assert_eq!(result, matrix!([1.0, 2.0], [3.0, 4.0]));
    }

    #[test]
    fn test_mul_matrix() {
        let matrix1 = matrix!([1.0, 2.0], [3.0, 4.0]);
        let matrix2 = matrix!([5.0, 6.0], [7.0, 8.0]);
        let result = (matrix1 * matrix2).unwrap();
        assert_eq!(result, matrix!([19.0, 22.0], [43.0, 50.0]));
    }

    #[test]
    fn test_mul_matrix_error() {
        let matrix1 = matrix!([1.0, 2.0], [3.0, 4.0]);
        let matrix2 = matrix!([5.0, 6.0]);
        let result = matrix1 * matrix2;
        assert_eq!(result, Err(MatrixError::DimensionMismatch));
    }

    #[test]
    fn test_index() {
        let matrix = matrix!([1.0, 2.0], [3.0, 4.0]);
        assert_eq!(matrix[(0, 0)], lnum!(1.0));
        assert_eq!(matrix[(1, 1)], lnum!(4.0));
    }

    #[test]
    fn test_index_mut() {
        let mut matrix = matrix!([1.0, 2.0], [3.0, 4.0]);
        matrix[(0, 0)] = lnum!(5.0);
        assert_eq!(matrix[(0, 0)], lnum!(5.0));
    }

    #[test]
    fn test_to_string() {
        let matrix = matrix!([1.0, 2.0], [3.0, 4.0]);
        assert_eq!(matrix.to_string(), "[ 1 2 ]\n[ 3 4 ]\n");
    }

}
