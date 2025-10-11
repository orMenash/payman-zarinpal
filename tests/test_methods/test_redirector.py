from zarinpal.methods.redirector import PaymentRedirector


class DummyZarinPal(PaymentRedirector):
    _BASE_DOMAIN = {True: "sandbox.zarinpal.com", False: "www.zarinpal.com"}
    sandbox = False


def test_redirect_url_construction():
    z = DummyZarinPal()
    url = z.get_payment_redirect_url("AUTH123")
    assert "StartPay/AUTH123" in url
