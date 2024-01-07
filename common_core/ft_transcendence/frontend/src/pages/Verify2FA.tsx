import React, {useState} from "react";
import axios from 'axios';
import {useNavigate} from "react-router-dom";


const Verify2FA: React.FC = () => {
    const history = useNavigate();
    const [otp, setOTP] = useState<string>('');

    const handleOTPChange = () => {
        console.log("OTP: " + otp);
        sendOTPToBackend(otp);
    };

    const sendOTPToBackend = async (otp: string) => {
        const response = await axios.patch('/auth/2fa/verify', {code: otp});
        if (response.data.isValid) {
            localStorage.setItem("auth_token", response.data.token);
            window.location.href = "/";
        } else {
            console.log("Code 2fa invalide.");
        }
    };

    return (
        <div className="flex flex-col h-screen w-screen justify-center items-center">
            <div className={"flex flex-col justify-center items-center bg-gray-200 p-4 rounded-lg gap-4"}>
                <h1 className='text-2xl font-bold'>Enter OTP</h1>
                <input
                    type="text"
                    name="otp"
                    id="otp"
                    placeholder='Enter your OTP'
                    className='border-2 border-gray-900 rounded-lg p-2'
                    value={otp}
                    onChange={(e) => setOTP(e.target.value)}
                />
                <div className='flex flex-row justify-between w-full'>
                    <button className='bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md'
                            onClick={() => history("/login")}>Back
                    </button>
                    <button className='bg-gray-900 hover:bg-pink-500 text-white py-2 px-4 rounded-md'
                            onClick={handleOTPChange}>Submit
                    </button>
                </div>
            </div>
        </div>
    );
}

export default Verify2FA;