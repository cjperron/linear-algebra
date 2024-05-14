use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Sub, SubAssign};
use num_integer::gcd;

use crate::matrix::LinMatrix;

/// Creates a new `LinNum` instance with a rational number.
#[macro_export]
macro_rules! lnum {
    ($value:expr) => {
        LinNum::new_real($value)
    };
}
// pub(crate) use lnum;


#[derive(Debug, PartialEq, Clone, Copy, PartialOrd)]
enum LinNumWrapper {
    Rational(i128, i128),
    Real(f64),
}
#[derive(Debug, PartialEq, Clone, Copy, PartialOrd)]
/// Represents a linear number, which can be either a rational number or a real number.
pub struct LinNum {
    value: LinNumWrapper,
}

impl LinNum {
    /// Creates a new `LinNum` instance with a rational number.
    ///
    /// # Arguments
    ///
    /// * `numerator` - The numerator of the rational number.
    /// * `denominator` - The denominator of the rational number.
    ///
    /// # Returns
    ///
    /// A new `LinNum` instance with the specified rational number.
    pub fn new_rational(numerator: i128, denominator: i128) -> LinNum {
        let gcd = gcd(numerator, denominator);
        let simplified_numerator = numerator / gcd;
        let simplified_denominator = denominator / gcd;
        LinNum {
            value: LinNumWrapper::Rational(simplified_numerator, simplified_denominator),
        }
    }

    /// Creates a new `LinNum` instance with a real number.
    ///
    /// # Arguments
    ///
    /// * `value` - The value of the real number.
    ///
    /// # Returns
    ///
    /// A new `LinNum` instance with the specified real number.
    pub fn new_real(value: f64) -> LinNum {
        LinNum {
            value: LinNumWrapper::Real(value),
        }
    }

    /// Checks if the `LinNum` instance represents a rational number.
    ///
    /// # Returns
    ///
    /// `true` if the `LinNum` instance represents a rational number, `false` otherwise.
    pub fn is_rational(&self) -> bool {
        matches!(self.value, LinNumWrapper::Rational(_, _))
    }

    /// Checks if the `LinNum` instance represents a real number.
    ///
    /// # Returns
    ///
    /// `true` if the `LinNum` instance represents a real number, `false` otherwise.
    pub fn is_real(&self) -> bool {
        matches!(self.value, LinNumWrapper::Real(_))
    }

    pub fn to_rational(self) -> Self {
        match self.value {
            LinNumWrapper::Real(val) => {
                let mut numerator = val.round() as i128;
                let mut denominator = 1;
                let mut error = (val - numerator as f64).abs();
                for i in 2..=100 {
                    let new_numerator = (val * i as f64).round() as i128;
                    let new_denominator = i;
                    let new_error = (val - new_numerator as f64 / new_denominator as f64).abs();
                    if new_error < error {
                        numerator = new_numerator;
                        denominator = new_denominator;
                        error = new_error;
                    }
                }
                LinNum::new_rational(numerator, denominator)
            }
            _ => self,
        }
    }

    pub fn to_real(self) -> Self {
        match self.value {
            LinNumWrapper::Rational(num, den) => {
                let val = num as f64 / den as f64;
                LinNum::new_real(val)
            }
            _ => self,
        }
    }
}

impl std::fmt::Display for LinNum {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self.value {
            LinNumWrapper::Rational(num, den) => {
                if den == 1 {
                    write!(f, "{}", num)
                } else {
                    write!(f, "{}/{}", num, den)
                }
            }
            LinNumWrapper::Real(val) => write!(f, "{}", val),
        }
    }
}

impl From<i128> for LinNum {
    fn from(value: i128) -> LinNum {
        LinNum::new_rational(value, 1)
    }
}

impl From<f64> for LinNum {
    fn from(value: f64) -> LinNum {
        LinNum::new_real(value)
    }
}

impl From<LinNum> for f64 {
    fn from(linnum: LinNum) -> f64 {
        match linnum.value {
            LinNumWrapper::Rational(num, den) => num as f64 / den as f64,
            LinNumWrapper::Real(val) => val,
        }
    }
}

impl From<LinNum> for i128 {
    fn from(linnum: LinNum) -> i128 {
        match linnum.value {
            LinNumWrapper::Rational(numer, denom) => numer / denom,
            LinNumWrapper::Real(val) => val as i128,
        }
    }
}

impl Add for LinNum {
    type Output = LinNum;

    fn add(self, other: LinNum) -> LinNum {
        match (self.value, other.value) {
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Rational(num2, den2)) => {
                let numerator = num1 * den2 + num2 * den1;
                let denominator = den1 * den2;
                LinNum::new_rational(numerator, denominator)
            }
            (LinNumWrapper::Real(val1), LinNumWrapper::Rational(num2, den2)) => {
                LinNum::new_real(val1 + (num2 as f64 / den2 as f64))
            }
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Real(val2)) => {
                LinNum::new_real((num1 as f64 / den1 as f64) + val2)
            }
            (LinNumWrapper::Real(val1), LinNumWrapper::Real(val2)) => LinNum::new_real(val1 + val2),

        }
    }
}

impl Mul<LinMatrix> for LinNum {
    type Output = LinMatrix;

    fn mul(self, other: LinMatrix) -> LinMatrix {
        other * self
    }
}

impl Sub for LinNum {
    type Output = LinNum;

    fn sub(self, other: LinNum) -> LinNum {
        match (self.value, other.value) {
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Rational(num2, den2)) => {
                let numerator = num1 * den2 - num2 * den1;
                let denominator = den1 * den2;
                LinNum::new_rational(numerator, denominator)
            }
            (LinNumWrapper::Real(val1), LinNumWrapper::Rational(num2, den2)) => {
                LinNum::new_real(val1 - (num2 as f64 / den2 as f64))
            }
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Real(val2)) => {
                LinNum::new_real((num1 as f64 / den1 as f64) - val2)
            }
            (LinNumWrapper::Real(val1), LinNumWrapper::Real(val2)) => LinNum::new_real(val1 - val2),
        }
    }
}

impl Mul for LinNum {
    type Output = LinNum;

    fn mul(self, other: LinNum) -> LinNum {
        match (self.value, other.value) {
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Rational(num2, den2)) => {
                let numerator = num1 * num2;
                let denominator = den1 * den2;
                LinNum::new_rational(numerator, denominator)
            }
            (LinNumWrapper::Real(val1), LinNumWrapper::Real(val2)) => LinNum::new_real(val1 * val2),
            (LinNumWrapper::Real(val1), LinNumWrapper::Rational(num2, den2)) => {
                LinNum::new_real(val1 * (num2 as f64 / den2 as f64))
            }
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Real(val2)) => {
                LinNum::new_real((num1 as f64 / den1 as f64) * val2)
            }
        }
    }
}

impl Div for LinNum {
    type Output = LinNum;

    fn div(self, other: LinNum) -> LinNum {
        match (self.value, other.value) {
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Rational(num2, den2)) => {
                let numerator = num1 * den2;
                let denominator = den1 * num2;
                LinNum::new_rational(numerator, denominator)
            }
            (LinNumWrapper::Real(val1), LinNumWrapper::Real(val2)) => LinNum::new_real(val1 / val2),
            (LinNumWrapper::Real(val1), LinNumWrapper::Rational(num2, den2)) => {
                LinNum::new_real(val1 / (num2 as f64 / den2 as f64))
            }
            (LinNumWrapper::Rational(num1, den1), LinNumWrapper::Real(val2)) => {
                LinNum::new_real((num1 as f64 / den1 as f64) / val2)
            }
        }
    }
}

impl AddAssign for LinNum {
    fn add_assign(&mut self, other: LinNum) {
        *self = *self + other;
    }
}

impl SubAssign for LinNum {
    fn sub_assign(&mut self, other: LinNum) {
        *self = *self - other;
    }
}

impl MulAssign for LinNum {
    fn mul_assign(&mut self, other: LinNum) {
        *self = *self * other;
    }
}

impl DivAssign for LinNum {
    fn div_assign(&mut self, other: LinNum) {
        *self = *self / other;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_new_rational() {
        let linnum = LinNum::new_rational(2, 4);
        assert!(linnum.is_rational());
        assert!(!linnum.is_real());
    }
    #[test]
    fn test_new_real() {
        let linnum = LinNum::new_real(2.0);
        assert!(!linnum.is_rational());
        assert!(linnum.is_real());
    }
    #[test]
    fn test_add_rational() {
        let linnum1 = LinNum::new_rational(2, 4);
        let linnum2 = LinNum::new_rational(1, 4);
        let result = linnum1 + linnum2;
        assert!(result.is_rational());
        match result.value {
            LinNumWrapper::Rational(num, den) => {
                assert_eq!(num, 3);
                assert_eq!(den, 4);
            }
            _ => panic!("Expected Rational value"),
        }
    }

    #[test]
    fn test_add_real() {
        let linnum1 = LinNum::new_real(2.0);
        let linnum2 = LinNum::new_real(1.0);
        let result = linnum1 + linnum2;
        assert!(result.is_real());
        match result.value {
            LinNumWrapper::Real(val) => {
                assert_eq!(val, 3.0);
            }
            _ => panic!("Expected Real value"),
        }
    }

    #[test]
    fn test_sub_rational() {
        let linnum1 = LinNum::new_rational(2, 4);
        let linnum2 = LinNum::new_rational(1, 4);
        let result = linnum1 - linnum2;
        assert!(result.is_rational());
        match result.value {
            LinNumWrapper::Rational(num, den) => {
                assert_eq!(num, 1);
                assert_eq!(den, 4);
            }
            _ => panic!("Expected Rational value"),
        }
    }

    #[test]
    fn test_sub_real() {
        let linnum1 = LinNum::new_real(2.0);
        let linnum2 = LinNum::new_real(1.0);
        let result = linnum1 - linnum2;
        assert!(result.is_real());
        match result.value {
            LinNumWrapper::Real(val) => {
                assert_eq!(val, 1.0);
            }
            _ => panic!("Expected Real value"),
        }
    }

    #[test]
    fn test_mul_rational() {
        let linnum1 = LinNum::new_rational(2, 4);
        let linnum2 = LinNum::new_rational(1, 4);
        let result = linnum1 * linnum2;
        assert!(result.is_rational());
        match result.value {
            LinNumWrapper::Rational(num, den) => {
                assert_eq!(num, 1);
                assert_eq!(den, 8);
            }
            _ => panic!("Expected Rational value"),
        }
    }

    #[test]
    fn test_mul_real() {
        let linnum1 = LinNum::new_real(2.0);
        let linnum2 = LinNum::new_real(1.0);
        let result = linnum1 * linnum2;
        assert!(result.is_real());
        match result.value {
            LinNumWrapper::Real(val) => {
                assert_eq!(val, 2.0);
            }
            _ => panic!("Expected Real value"),
        }
    }

    #[test]
    fn test_div_rational() {
        let linnum1 = LinNum::new_rational(2, 4);
        let linnum2 = LinNum::new_rational(1, 4);
        let result = linnum1 / linnum2;
        assert!(result.is_rational());
        match result.value {
            LinNumWrapper::Rational(num, den) => {
                assert_eq!(num, 2);
                assert_eq!(den, 1);
            }
            _ => panic!("Expected Rational value"),
        }
    }

    #[test]
    fn test_div_real() {
        let linnum1 = LinNum::new_real(2.0);
        let linnum2 = LinNum::new_real(1.0);
        let result = linnum1 / linnum2;
        assert!(result.is_real());
        match result.value {
            LinNumWrapper::Real(val) => {
                assert_eq!(val, 2.0);
            }
            _ => panic!("Expected Real value"),
        }
    }

    #[test]
    fn test_to_string_rational() {
        let linnum = LinNum::new_rational(2, 4);
        assert_eq!(linnum.to_string(), "1/2");
    }

    #[test]
    fn test_to_string_real() {
        let linnum = LinNum::new_real(2.0);
        assert_eq!(linnum.to_string(), "2");
    }

    #[test]
    fn test_from_i128() {
        let linnum: LinNum = 2.into();
        assert!(linnum.is_rational());
        assert_eq!(linnum, LinNum::new_rational(2, 1));
    }

    #[test]
    fn test_from_f64() {
        let linnum: LinNum = 2.0.into();
        assert!(linnum.is_real());
        assert_eq!(linnum, LinNum::new_real(2.0));
    }

    #[test]
    fn test_to_real() {
        let linnum = LinNum::new_rational(2, 1);
        let result = linnum.to_real();
        assert!(result.is_real());
        assert_eq!(result, LinNum::new_real(2.0));
    }

    #[test]
    fn test_to_rational() {
        let linnum = LinNum::new_real(1.5);
        let result = linnum.to_rational();
        assert!(result.is_rational());
        assert_eq!(result, LinNum::new_rational(3, 2));
    }
}
