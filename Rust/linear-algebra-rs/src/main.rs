use linear_algebra_rs::matrix;
use linear_algebra_rs::matrix::LinMatrix;
use linear_algebra_rs::lnum;
use linear_algebra_rs::linnum::LinNum;



fn main() -> Result<(), std::io::Error> {
    
    let m1 = matrix!([1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]);
    println!("{}", m1);
    let m2 = lnum!(2.0) * matrix!([1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]);
    println!("{}", m2.transpose());
    let m3 = (m1 + m2).unwrap();
    println!("{}", m3);

    let m4 = matrix!([1.0, 2.0], [3.0, 4.0]);
    println!("{}", m4);
    println!("{}", m4.determinant().unwrap());

    let m5 = matrix!([1.0, 2.0, 3.0], [4.0, 5.0, 6.0], [7.0, 8.0, 9.0]);
    println!("{}", m5);
    println!("{}", m5.determinant().unwrap());

    Ok(())
}