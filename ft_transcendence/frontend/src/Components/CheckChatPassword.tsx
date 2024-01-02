import React from "react";

function CheckPassword(password: string) {

    if (password.length < 8) {
        return false;
    }

    const hasUppercase = /[A-Z]/.test(password);
    const hasLowercase = /[a-z]/.test(password);
    const hasNumber = /\d/.test(password);
    const hasSpecialChar = /[!@#$%^&*()_+{}\[\]:;<>,.?~\\-]/.test(password);

    return (hasUppercase && hasLowercase && hasNumber && hasSpecialChar);
}

export default CheckPassword;