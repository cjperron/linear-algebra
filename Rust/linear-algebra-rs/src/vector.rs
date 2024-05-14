use crate::linnum::LinNum;
use std::ops::{Add, AddAssign, Div, DivAssign, Index, IndexMut, Mul, MulAssign, Sub, SubAssign};

macro_rules! linvector {
    ($($x:expr),*) => {
        {
            let mut temp_vec: Vec<LinNum> = Vec::with_capacity(16);
            $(
                let x: LinNum = $x.into();
                temp_vec.push(x.to_real());
            )*
            LinVector { numbers: temp_vec }
        }
    };
}

/// Represents a vector as defined in standard linear algebra.
#[derive(Debug, PartialEq, Clone)]
pub struct LinVector {
    numbers: Vec<LinNum>,
}


impl LinVector {
    /// Returns the dimension of the vector.
    ///
    /// # Returns
    ///
    /// The number of elements in the vector.
    pub fn dim(&self) -> usize {
        self.numbers.len()
    }

    /// Computes the dot product of this vector with another vector.
    ///
    /// # Parameters
    ///
    /// - `other`: A reference to the other vector.
    ///
    /// # Returns
    ///
    /// The dot product of the two vectors.
    pub fn dot_product(&self, other: &LinVector) -> LinNum {
        let mut result = LinNum::new_real(0.0);
        for (num1, num2) in self.numbers.iter().zip(other.numbers.iter()) {
            result = result + (*num1 * *num2);
        }
        result
    }

    /// Computes the cross product of this vector with another vector.
    ///
    /// # Parameters
    ///
    /// - `other`: A reference to the other vector.
    ///
    /// # Returns
    ///
    /// - `Some<LinVector>`: The cross product of the two vectors if they are both 3-dimensional.
    /// - `None`: If either vector is not 3-dimensional.
    pub fn cross_product(&self, other: &LinVector) -> Option<LinVector> {
        if self.dim() != 3 || other.dim() != 3 {
            return None;
        }
        let x = self.numbers[1] * other.numbers[2] - self.numbers[2] * other.numbers[1];
        let y = self.numbers[2] * other.numbers[0] - self.numbers[0] * other.numbers[2];
        let z = self.numbers[0] * other.numbers[1] - self.numbers[1] * other.numbers[0];
        Some(linvector![x, y, z])
    }

    pub fn real_numbers(self) -> Self {
        let mut result = Vec::new();
        for num in self.numbers.iter() {
            result.push(num.to_real());
        }
        LinVector { numbers: result }
    }

    pub fn rational_numbers(self) -> Self {
        let mut result = Vec::new();
        for num in self.numbers.iter() {
            result.push(num.to_rational());
        }
        LinVector { numbers: result }
    }
}

impl ToString for LinVector {
    fn to_string(&self) -> String {
        let mut result = String::from("[");
        for (i, num) in self.numbers.iter().enumerate() {
            result.push_str(&num.to_string());
            if i < self.numbers.len() - 1 {
                result.push_str(", ");
            }
        }
        result.push(']');
        result
    }
}

impl Add for LinVector {
    type Output = LinVector;

    fn add(self, other: LinVector) -> LinVector {
        let mut result = Vec::new();
        for (num1, num2) in self.numbers.iter().zip(other.numbers.iter()) {
            result.push(*num1 + *num2);
        }
        LinVector { numbers: result }
    }
}

impl Sub for LinVector {
    type Output = LinVector;

    fn sub(self, other: LinVector) -> LinVector {
        let mut result = Vec::new();
        for (num1, num2) in self.numbers.iter().zip(other.numbers.iter()) {
            result.push(*num1 - *num2);
        }
        LinVector { numbers: result }
    }
}

impl Mul<LinNum> for LinVector {
    type Output = LinVector;

    fn mul(self, other: LinNum) -> LinVector {
        let mut result = Vec::new();
        for num in self.numbers.iter() {
            result.push(num.to_real() * other.to_real());
        }
        LinVector { numbers: result }
    }
}

impl Div<LinNum> for LinVector {
    type Output = LinVector;

    fn div(self, other: LinNum) -> LinVector {
        let mut result = Vec::new();
        for num in self.numbers.iter() {
            result.push(num.to_real() / other.to_real());
        }
        LinVector { numbers: result }
    }
}

impl MulAssign<LinNum> for LinVector {
    fn mul_assign(&mut self, other: LinNum) {
        for num in self.numbers.iter_mut() {
            *num = num.to_real() * other.to_real();
        }
    }
}

impl DivAssign<LinNum> for LinVector {
    fn div_assign(&mut self, other: LinNum) {
        for num in self.numbers.iter_mut() {
            *num = num.to_real() / other.to_real();
        }
    }
}

impl AddAssign for LinVector {
    fn add_assign(&mut self, other: LinVector) {
        for (num1, num2) in self.numbers.iter_mut().zip(other.numbers.iter()) {
            *num1 = num1.to_real() + num2.to_real();
        }
    }
}

impl SubAssign for LinVector {
    fn sub_assign(&mut self, other: LinVector) {
        for (num1, num2) in self.numbers.iter_mut().zip(other.numbers.iter()) {
            *num1 = num1.to_real() - num2.to_real();
        }
    }
}

impl IntoIterator for LinVector {
    type Item = LinNum;
    type IntoIter = std::vec::IntoIter<LinNum>;

    fn into_iter(self) -> Self::IntoIter {
        self.numbers.into_iter()
    }
}

impl Index<usize> for LinVector {
    type Output = LinNum;

    fn index(&self, index: usize) -> &Self::Output {
        &self.numbers[index]
    }
}

impl IndexMut<usize> for LinVector {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output {
        &mut self.numbers[index]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_dim() {
        let vec = linvector![1, 2, 3];
        assert_eq!(vec.dim(), 3);
    }

    #[test]
    fn test_dot_product() {
        let vec1 = linvector![1, 2, 3];
        let vec2 = linvector![4, 5, 6];
        assert_eq!(vec1.dot_product(&vec2), LinNum::new_real(32.0));
    }

    #[test]
    fn test_cross_product() {
        let vec1 = linvector![1, 2, 3];
        let vec2 = linvector![4, 5, 6];
        let result = vec1.cross_product(&vec2).unwrap();
        assert_eq!(result, linvector![-3, 6, -3]);
    }

    #[test]
    fn test_to_string() {
        let vec = linvector![1, 2, 3];
        assert_eq!(vec.to_string(), "[1, 2, 3]");
    }

    #[test]
    fn test_add() {
        let vec1 = linvector![1, 2, 3];
        let vec2 = linvector![4, 5, 6];
        let result = vec1 + vec2;
        assert_eq!(result, linvector![5, 7, 9]);
    }

    #[test]
    fn test_sub() {
        let vec1 = linvector![1, 2, 3];
        let vec2 = linvector![4, 5, 6];
        let result = vec1 - vec2;
        assert_eq!(result, linvector![-3, -3, -3]);
    }

    #[test]
    fn test_mul() {
        let vec = linvector![1, 2, 3];
        let result = vec * LinNum::new_real(2.0);
        assert_eq!(result, linvector![2, 4, 6]);
    }

    #[test]
    fn test_div() {
        let vec = linvector![2, 4, 6];
        let result = vec / LinNum::new_real(2.0);
        assert_eq!(result, linvector![1, 2, 3]);
    }

    #[test]
    fn test_mul_assign() {
        let mut vec = linvector![1, 2, 3];
        vec *= LinNum::new_real(2.0);
        assert_eq!(vec, linvector![2, 4, 6]);
    }

    #[test]
    fn test_div_assign() {
        let mut vec = linvector![2, 4, 6];
        vec /= LinNum::new_real(2.0);
        assert_eq!(vec, linvector![1, 2, 3]);
    }

    #[test]
    fn test_add_assign() {
        let mut vec1 = linvector![1, 2, 3];
        let vec2 = linvector![4, 5, 6];
        vec1 += vec2;
        assert_eq!(vec1, linvector![5, 7, 9]);
    }

    #[test]
    fn test_sub_assign() {
        let mut vec1 = linvector![1, 2, 3];
        let vec2 = linvector![4, 5, 6];
        vec1 -= vec2;
        assert_eq!(vec1, linvector![-3, -3, -3]);
    }

    #[test]
    fn test_index() {
        let vec = linvector![1, 2, 3];
        assert_eq!(vec[0], LinNum::new_real(1.0));
        assert_eq!(vec[1], LinNum::new_real(2.0));
        assert_eq!(vec[2], LinNum::new_real(3.0));
    }

    #[test]
    fn test_index_mut() {
        let mut vec = linvector![1, 2, 3];
        vec[0] = LinNum::new_real(4.0);
        vec[1] = LinNum::new_real(5.0);
        vec[2] = LinNum::new_real(6.0);
        assert_eq!(vec, linvector![4, 5, 6]);
    }

    #[test]
    fn test_iterator() {
        let vec = linvector![1, 2, 3];
        let mut iter = vec.into_iter();
        assert_eq!(iter.next(), Some(LinNum::new_real(1.0)));
        assert_eq!(iter.next(), Some(LinNum::new_real(2.0)));
        assert_eq!(iter.next(), Some(LinNum::new_real(3.0)));
        assert_eq!(iter.next(), None);
    }


}