import axios from "axios";

const API_URL = `${process.env.REACT_APP_BACKEND_URL}/auth/`;

class AuthService {
  login(username: string, password: string) {
    return axios
      .post(API_URL + "login", {
      })
      .then(response => {
        if (response.data.accessToken) {
            localStorage.setItem("auth_token", JSON.stringify(response.data));
        }

        return response.data;
      });
  }

  logout() {
    localStorage.removeItem("user");
  }

  register(username: string, email: string, password: string) {
    return axios.post(API_URL + "signup", {
      username,
      email,
      password
    });
  }

  getCurrentUser() {
    const userStr = localStorage.getItem("user");
    if (userStr) return JSON.parse(userStr);

    return null;
  }
}

export default new AuthService();
